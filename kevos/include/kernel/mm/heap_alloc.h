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

#ifndef _KEVOS_KERNEL_MM_HEAPMEM_H_
#define _KEVOS_KERNEL_MM_HEAPMEM_H_

#include <sys/types.h>

#include <cstddef>

namespace mm
{

class HeapMemory
{
public:
	HeapMemory()
	{
	}

	HeapMemory(std::size_t vStartAddr,std::size_t vEndAddr)
	{
		setup(vStartAddr,vEndAddr);
	}

	constexpr void setup(std::size_t vStartAddr,std::size_t vEndAddr)
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

	void* allocate(std::size_t size);

	void deallocate(void* ptr);

	void* reallocate(void* ptr,std::size_t newSize);

private:
	struct MemoryHeader
	{
		MemoryHeader* next;
		MemoryHeader* prev;
		std::size_t used;
	};

	MemoryHeader* m_memStart;
	MemoryHeader* m_memEnd;
};

}

#endif