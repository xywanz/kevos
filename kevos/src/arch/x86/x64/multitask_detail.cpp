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

#include <arch/x86/x64/multitask_detail.h>
#include <arch/x86/x64/gdt.h>
#include <arch/x86/x64/vm.h>
#include <kernel/mm/new.h>
#include <kernel/mm/page_alloc.h>

#include <cstdlib>

#include <cstring>


namespace multitask
{

constexpr std::size_t userCodeStart=0x100000000;
constexpr std::size_t userStackStart=0x0000FFFF00000000;

Process::Process(void* entry,TYPE type):pages()
{
    using namespace mm::page;
    using namespace mm::vm;
    if(type==USER)
    {
        auto stackPPN=PageAllocator::allocate();
        auto codePPN=PageAllocator::allocate();
        auto stack=reinterpret_cast<void*>(VirtualMemory::getAddressFromPPN(stackPPN));
        auto code=reinterpret_cast<void*>(VirtualMemory::getAddressFromPPN(codePPN));
        pages.push_back(stack);
        pages.push_back(code);

        std::memcpy(code,entry,pageSize);

        vm=new VirtualMemory;
        auto mm=getVM<VirtualMemory>();
        mm->mapKernelSpace();
        mm->mapPage(userCodeStart/pageSize,codePPN,1);
        mm->mapPage(userStackStart/pageSize,stackPPN,1);

        // regs=(void*)ProcessManager::createUserRegInfo(
        //     (void*)userCodeStart,
        //     (void*)(userStackStart+pageSize),
        //     new char[pageSize]+pageSize,
        //     mm->getPML4PPN()*pageSize
        // );

        regs=(void*)ProcessManager::createUserRegInfo(
            entry,
            new char[pageSize]+pageSize,
            new char[pageSize]+pageSize,
            mm->getPML4PPN()*pageSize
        );
    }
    else
    {
        regs=(void*)ProcessManager::createKernelRegInfo(entry,new char[pageSize]+pageSize);
    }
    pid=generateNextPid();
}

Process::~Process()
{
    if(type==KERNEL)
    {
        if(auto kstack=getRegs<ProcessRegisters>()->rsp)
            delete reinterpret_cast<char*>(kstack);
    }
    else
    {
        if(auto stack=getRegs<ProcessRegisters>()->rsp0)
            delete reinterpret_cast<char*>(stack);
        for(auto page:pages)
        {
            mm::page::PageAllocator::deallocate(reinterpret_cast<std::size_t>(page)/mm::page::pageSize);
        }
    }        
}

std::list<Process*> ProcessManager::s_processes(nullptr);
typename ProcessManager::iterator ProcessManager::s_current(nullptr);


void ProcessManager::initialize()
{
    s_processes.empty_initialize();
    s_processes.push_back(new Process(0,Process::KERNEL));
    s_current=s_processes.begin();
}

ProcessRegisters* ProcessManager::createKernelRegInfo(void* entry,void* stack)
{
    ProcessRegisters* regs=new ProcessRegisters;
    std::memset(regs,0,sizeof(ProcessRegisters));
    regs->cs=__KERNEL_CS;
    regs->ds=__KERNEL_DS;
    regs->es=__KERNEL_DS;
    regs->ss=__KERNEL_DS;
    regs->fs=__KERNEL_DS;
    regs->gs=__KERNEL_DS;
    regs->rflags=0x200;
    regs->dpl=0;
    regs->rsp=reinterpret_cast<std::size_t>(stack);
    regs->rbp=reinterpret_cast<std::size_t>(stack);
    regs->rip=reinterpret_cast<std::size_t>(entry);
    regs->cr3=reinterpret_cast<std::size_t>(mm::page::kernel::pml4);
    return regs;
}

ProcessRegisters* ProcessManager::createUserRegInfo(void* entry,void* stack,void* kstack,std::size_t pml4)
{
    ProcessRegisters* regs=new ProcessRegisters;
    std::memset(regs,0,sizeof(ProcessRegisters));
    regs->cs=__USER_CS;
    regs->ds=__USER_DS;
    regs->es=__USER_DS;
    regs->ss=__USER_DS;
    regs->fs=__USER_DS;
    regs->gs=__USER_DS;
    regs->rflags=0x200;
    regs->dpl=3;
    regs->rsp=reinterpret_cast<std::size_t>(stack);
    regs->rbp=reinterpret_cast<std::size_t>(stack);
    regs->rsp0=reinterpret_cast<std::size_t>(kstack);
    regs->rip=reinterpret_cast<std::size_t>(entry);
    regs->cr3=pml4;
    return regs;
}

void ProcessManager::switchToNext()
{
    ++s_current;
    if(s_current==s_processes.end())
        s_current=s_processes.begin();
}

}
