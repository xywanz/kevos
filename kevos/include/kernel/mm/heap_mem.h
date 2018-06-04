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

namespace kernel::mm
{

class HeapMemory
{
public:
	HeapMemory(){}

	HeapMemory(size_t vStartAddr,size_t vEndAddr);

	void setup(size_t vStartAddr,size_t vEndAddr);

	void* allocate(size_t size);

	void deallocate(void* ptr);

	void* reallocate(void* ptr,size_t newSize);

private:
	struct MemoryHeader
	{
		MemoryHeader* next;
		MemoryHeader* prev;
		size_t used;
	};

	MemoryHeader* m_memStart;
	MemoryHeader* m_memEnd;
};

}	// end of namespace kernel::mm

#endif