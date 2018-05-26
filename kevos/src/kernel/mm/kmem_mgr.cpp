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

#include <kernel/mm/kmem_mgr.h>

KEVOS_NSS_2(kernel,mm);

KernMemManager::KernMemManager(size_t vStartPagePPN,size_t vEndPagePPN)
	:m_memStart(reinterpret_cast<MemHeader*>(vStartPagePPN*__PAGE_SIZE)),
	 m_memEnd(reinterpret_cast<MemHeader*>(vEndPagePPN*__PAGE_SIZE)-1)
{
	m_memEnd->next=nullptr;
	m_memEnd->prev=m_memStart;
	m_memEnd->used=1;
	m_memStart->next=m_memEnd;
	m_memStart->prev=nullptr;
	m_memStart->used=0;
}

void* KernMemManager::allocate(size_t size)
{
	size_t nsize=size+sizeof(MemHeader);
	for(auto block=m_memStart;block!=m_memEnd;block=block->next)
	{
		size_t blockSize=reinterpret_cast<size_t>(block->next)-reinterpret_cast<size_t>(block);
		if(block->used||blockSize<nsize)
			continue;
		block->used=1;
		size_t rest=blockSize-nsize;
		if(rest>sizeof(MemHeader))
		{
			MemHeader* nnode=reinterpret_cast<MemHeader*>(reinterpret_cast<char*>(block)+nsize);
			nnode->used=0;
			nnode->next=block->next;
			nnode->prev=block;
			block->next=nnode;
		}
		return block+1;
	}
	return 0;
}

void KernMemManager::deallocate(void* ptr)
{
	MemHeader* rnode=reinterpret_cast<MemHeader*>(ptr)-1;
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

KEVOS_NSE_2(mm,kernel);
