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
#include <arch/common/interrupt.h>
#include <arch/x86/common/cpuid.h>
#include <arch/x86/x64/gdt.h>
#include <arch/x86/x64/tss.h>
#include <arch/x86/x64/vm.h>
#include <arch/x86/x64/process.h>
#include <kernel/mm/mem_layout.h>
#include <kernel/mm/heap_mem.h>
#include <kernel/mm/kheap_mem.h>
#include <kernel/mm/page_mgr.h>
#include <kernel/mm/new.h>

#include <stdlib.h>
#include <stdio.h>

KEVOS_NSS_4(arch,x86,x64,boot);

using namespace kernel::mm;

void print(size_t pos,const char* buf)
{
	auto addr=(unsigned char*)(0xB8000+pos*2);
	for(size_t i=0;buf[i]!=0;++i)
	{
		addr[2*i]=buf[i];
		addr[2*i+1]=0x75;
	}
}

inline void confirmImAlive() {*((uint16_t*)(0xB8000+100))=0x7575;}

void test()
{
	VirtualMemory vm;
	vm.mapPage(0x1000000,PageManager::allocate(),1);
}

extern "C" void entry64()
{
	__asm__("mov %%rax, %%cr3" : : "a"(KernelPageFrame::pml4));
	TSS::initialize();
	GDT::initialize();
	KernelHeap::initialize();
	PageManager::initialize();
	arch::common::InterruptManager::initialize();
	arch::common::InterruptManager::enableInterrupts();
	arch::common::InterruptManager::enableTimer();
	common::CPUInfo cpuInfo=common::CPUInfo::instance();
	ProcessManager::initialize();

	int* b=new int;
	delete b;

	int* a=new int[5];
	delete[]  a;

	char buf[16];
	itoa(PageManager::allocate(),buf,16);
	print(0,buf);

	itoa(PageManager::allocate(),buf,16);
	print(30,buf);

	size_t pnn=PageManager::allocate();
	PageManager::deallocate(pnn);

	VirtualMemory vm;
	vm.mapPage(0,PageManager::allocate(),1);

	test();

	confirmImAlive();
	while(1);
}


KEVOS_NSE_4(boot,x64,x86,arch);
