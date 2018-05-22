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

#include <sys/portable.h>
#include <arch/x64/mem_layout.h>
#include <kernel/mm/kmem_mgr.h>
#include <kernel/mm/page_mgr.h>
#include <arch/x64/vm.h>

KEVOS_NSS_4(kevos,arch,x64,boot);


	kernel::mm::KernMemManager kmm(
		reinterpret_cast<size_t>(&kheap_start_address)>>12,
		reinterpret_cast<size_t>(&kheap_end_address)>>12
	);

extern "C" void entry64()
{
	while(1);
}


KEVOS_NSE_4(boot,x64,arch,kevos);
