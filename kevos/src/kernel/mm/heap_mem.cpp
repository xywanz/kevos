/* Copyright 2018 kevin Lau (http://github.com/stormycatcat)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include <kernel/mm/heap_mem.h>

#include <cstring>

KEVOS_NSS_2(kernel,mm);

HeapMemory::HeapMemory(size_t vStartAddr,size_t vEndAddr)
	:m_memStart(reinterpret_cast<MemoryHeader*>(vStartAddr)),
	 m_memEnd(reinterpret_cast<MemoryHeader*>(vEndAddr)-1)
{
	m_memEnd->next=nullptr;
	m_memEnd->prev=m_memStart;
	m_memEnd->used=1;
	m_memStart->next=m_memEnd;
	m_memStart->prev=nullptr;
	m_memStart->used=0;
}

void HeapMemory::setup(size_t vStartAddr,size_t vEndAddr)
{
	m_memStart=reinterpret_cast<MemoryHeader*>(vStartAddr),
	m_memEnd=reinterpret_cast<MemoryHeader*>(vEndAddr)-1;
	m_memEnd->next=nullptr;
	m_memEnd->prev=m_memStart;
	m_memEnd->used=1;
	m_memStart->next=m_memEnd;
	m_memStart->prev=nullptr;
	m_memStart->used=0;
}

void* HeapMemory::allocate(size_t size)
{
	size_t nsize=size+sizeof(MemoryHeader);
	for(auto block=m_memStart;block!=m_memEnd;block=block->next)
	{
		size_t blockSize=reinterpret_cast<size_t>(block->next)-reinterpret_cast<size_t>(block);
		if(block->used||blockSize<nsize)
			continue;
		block->used=1;
		size_t rest=blockSize-nsize;
		if(rest>sizeof(MemoryHeader))
		{
			MemoryHeader* nnode=reinterpret_cast<MemoryHeader*>(reinterpret_cast<char*>(block)+nsize);
			nnode->used=0;
			nnode->next=block->next;
			nnode->prev=block;
			block->next=nnode;
		}
		return block+1;
	}
	return 0;
}

void HeapMemory::deallocate(void* ptr)
{
	MemoryHeader* rnode=reinterpret_cast<MemoryHeader*>(ptr)-1;
	rnode->used=0;
	if(!rnode->prev->used)
	{
		rnode->prev->next=rnode->next;
		rnode->next->prev=rnode->prev;
		rnode=rnode->prev;
	}
	if(!rnode->next->used)
	{
		rnode->next->next->prev=rnode;
		rnode->next=rnode->next->next;
	}
}

void* HeapMemory::reallocate(void* ptr,size_t newSize)
{
	auto hdr=reinterpret_cast<MemoryHeader*>(ptr)-1;
	MemoryHeader* next=hdr->next;
	size_t origin=reinterpret_cast<size_t>(hdr->next)-reinterpret_cast<size_t>(hdr)-sizeof(MemoryHeader);
	size_t total=newSize+sizeof(MemoryHeader);
	size_t max=next->next-hdr;
	if(next-hdr>=total)
	{
		return ptr;	
	}
	if(!next->used&&max>=total)
	{
		if(max-total<=sizeof(MemoryHeader))
		{
			hdr->next=next->next;
			hdr->next->prev=hdr;
			return ptr;
		}
		MemoryHeader* nhdr=reinterpret_cast<MemoryHeader*>(reinterpret_cast<char*>(hdr)+total);
		nhdr->next=hdr->next;
		nhdr->prev=hdr;
		hdr->next=nhdr;
		return ptr;
	}
	deallocate(ptr);
	for(auto block=m_memStart;block!=m_memEnd;block=block->next)
	{
		size_t blockSize=reinterpret_cast<size_t>(block->next)-reinterpret_cast<size_t>(block);
		if(block->used||blockSize<total)
			continue;
		block->used=1;
		std::memmove(block+1,ptr,origin);
		size_t rest=blockSize-total;
		if(rest>sizeof(MemoryHeader))
		{
			MemoryHeader* nnode=reinterpret_cast<MemoryHeader*>(reinterpret_cast<char*>(block)+total);
			nnode->used=0;
			nnode->next=block->next;
			nnode->prev=block;
			block->next=nnode;
		}
		return block+1;
	}
}

KEVOS_NSE_2(mm,kernel);
