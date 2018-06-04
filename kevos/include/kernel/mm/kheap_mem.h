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

#ifndef _KEVOS_KERNEL_MM_KHEAPMEM_H_
#define _KEVOS_KERNEL_MM_KHEAPMEM_H_

#include <kernel/mm/heap_mem.h>

namespace kernel::mm
{

class KernelHeap
{
public:
	static void initialize();

	static void* allocate(size_t size)
	{
		return khm.allocate(size);
	}

	static void deallocate(void* ptr)
	{
		khm.deallocate(ptr);
	}

	static void* reallocate(void* ptr,size_t newSize)
	{
		khm.reallocate(ptr,newSize);
	}

private:
	static HeapMemory khm;
};

}	//end of namespace kernel::mm

#endif