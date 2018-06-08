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

extern "C"{ 
    void* __cxa_atexit=0;
    void* __dso_handle = 0;
}

#include <arch/common/interrupt.h>
#include <arch/common/assert.h>
#include <arch/x86/common/cpuid.h>
#include <arch/x86/x64/gdt.h>
#include <arch/x86/x64/tss.h>
#include <arch/x86/x64/vm.h>
#include <arch/x86/x64/process.h>
#include <kernel/mm/kheap_mem.h>
#include <kernel/mm/mem_layout.h>

#include <kernel/mm/page_mgr.h>
#include <kernel/mm/new.h>

#include <cstdlib>
#include <cstdio>

#include <cmath>

#include <memory>

#include <array>
#include <vector>
#include <list>
#include <stack>


void test_utility_main();
void test_concept_main();
void test_cxx_stdlib_template_main();
void test_vector_main();
void test_list_main();
void test_array_main();
void test_deque_main();
void test_multiprocess_main();

namespace arch::x86::x64::boot
{

using namespace kernel::mm;

std::size_t print(std::size_t pos,const char* buf)
{
    auto addr=(unsigned char*)(0xB8000+pos*2);
    std::size_t i;
    for(i=0;buf[i]!=0;++i)
    {
        addr[2*i]=buf[i];
        addr[2*i+1]=0x75;
    }
    return pos+160;
}

inline void confirmImAlive() 
{
	*((uint16_t*)(0xB8000+150))=0x7500+'k';
	*((uint16_t*)(0xB8000+152))=0x7500+'e';
	*((uint16_t*)(0xB8000+154))=0x7500+'v';
	*((uint16_t*)(0xB8000+156))=0x7500+'o';
	*((uint16_t*)(0xB8000+158))=0x7500+'s';
}


extern "C" void entry64()
{
	VirtualMemory::loadKernelPML4();
	TSS::initialize();
	GDT::initialize();
	KernelHeap::initialize();
	PageManager::initialize();
	arch::common::InterruptManager::initialize();
	arch::common::InterruptManager::enableInterrupts();
	arch::common::InterruptManager::enableTimer();
	arch::common::InterruptManager::setTimerFrequency(1);
	common::CPUInfo& cpuInfo=common::CPUInfo::instance();
	ProcessManager::initialize();

	test_utility_main();
	test_concept_main();
	test_cxx_stdlib_template_main();
	test_vector_main();
	test_list_main();
	test_array_main();
	test_deque_main();
    test_multiprocess_main();

	confirmImAlive();
	while(1)
        *((uint16_t*)(0xB8000))=((std::rand()%128)<<8)+'k';
}


}	// end of namespace arch::x86::x64::boot
