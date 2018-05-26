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
#include <arch/x86/x64/mem_layout.h>
#include <arch/x86/x64/gdt.h>
#include <arch/x86/x64/vm.h>
#include <kernel/mm/kmem_mgr.h>
#include <kernel/mm/page_mgr.h>
#include <arch/x86/common/cpuid.h>
#include <arch/common/interrupt.h>

KEVOS_NSS_4(arch,x86,x64,boot);

using namespace kernel::mm;


extern "C" void entry64()
{
	__asm__("movq %[stack],%%rsp": : [stack]"i"((uint64_t)&kstack_end_address-0x10000));

	__asm__("mov %%rax, %%cr3" : : "a"(__knPML4));

	struct __packed__ GDTPointer
    {
        uint16_t limit;
        uint64_t address;
    } gdtPtr;
    gdtPtr.limit=sizeof(__knGDT)-1;
    gdtPtr.address=reinterpret_cast<uint64_t>(__knGDT);
    __asm__("lgdt %[gdtr]" : : [gdtr]"m"(gdtPtr));



	KernMemManager kmm(reinterpret_cast<uint64_t>(&kheap_start_address)>>12,
		reinterpret_cast<uint64_t>(&kheap_end_address)>>12);
	void* ptr=kmm.allocate(1);
	kmm.deallocate(ptr);

	PageManager pm;

	common::CPUInfo cpuInfo;

	arch::common::InterruptManager::initialize();

	*((uint16_t*)(0xB8000))=0x7575;
	while(1);
}


KEVOS_NSE_4(boot,x64,x86,arch);
