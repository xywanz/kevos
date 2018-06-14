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

#ifndef _KEVOS_ARCH_X86_X64_PROCESS_H_
#define _KEVOS_ARCH_X86_X64_PROCESS_H_

#include <sys/types.h>
#include <kernel/multitask/process.h>
#include <arch/x86/x64/vm.h>

#include <list>

namespace multitask
{

struct ProcessRegisters
{
    uint64_t rip;
    uint64_t rflags;
    uint64_t cs;
    uint64_t ds;
    uint64_t es;
    uint64_t fs;
    uint64_t gs;
    uint64_t ss;
    uint64_t rsp;
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t dpl;
    uint64_t rsp0;
    uint64_t ss0;
    uint64_t cr3;
    uint32_t fpu[28];
};


class ProcessManager
{
public:
    static void initialize();

    static ProcessRegisters* createKernelRegInfo(void* entry,void* stack);

    static ProcessRegisters* createUserRegInfo(void* entry,void* stack,void* kstack,std::size_t pml4);

    static void setInstructionPointer(Process* process,void* entry)
    {
        process->getRegs<ProcessRegisters>()->rip=(uint64_t)entry;
    }

    static void setVirtualMemory(Process* process,const mm::vm::VirtualMemory& mm);

    static void switchToNext();

    static void contextSwitch();

    static void createKernelProcess(void* entry)
    {
        s_processes.push_back(new Process(entry,Process::KERNEL));
    }

    static void createUserProcess(void* entry)
    {
        s_processes.push_back(new Process(entry,Process::USER));
    }

    static Process* current()
    {
        return *s_current;
    }
private:
    static std::list<Process*> s_processes;

    using iterator=typename std::list<Process*>::iterator;

    static iterator s_current;
};

} 

#endif
