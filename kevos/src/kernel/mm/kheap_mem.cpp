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

#include <kernel/mm/kheap_mem.h>
#include <kernel/mm/mem_layout.h>

KEVOS_NSS_2(kernel,mm);

HeapMemory KernelHeap::khm;

void KernelHeap::initialize()
{
	khm.setup(reinterpret_cast<size_t>(&kheap_start_address),
		reinterpret_cast<size_t>(&kheap_end_address));
}

KEVOS_NSE_2(mm,kernel);
