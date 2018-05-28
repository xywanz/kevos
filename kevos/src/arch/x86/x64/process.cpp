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

#include <arch/x86/x64/process.h>
#include <arch/x86/x64/gdt.h>
#include <arch/x86/x64/vm.h>
#include <kernel/mm/new.h>

KEVOS_NSS_3(arch,x86,x64);

ProcessRegs* ProcessManager::createKernelRegsInfo(void* entry,void* stack)
{
    ProcessRegs* regs=new ProcessRegs;
    regs->cs=__KERNEL_CS;
    regs->ds=__KERNEL_DS;
    regs->es=__KERNEL_DS;
    regs->ss=__KERNEL_DS;
    regs->fs=__KERNEL_DS;
    regs->gs=__KERNEL_DS;
    regs->rflags=0x200;
    regs->dpl=0;
    regs->rsp=reinterpret_cast<uint64_t>(stack);
    regs->rbp=reinterpret_cast<uint64_t>(stack);
    regs->rip=reinterpret_cast<uint64_t>(entry);
    regs->cr3=reinterpret_cast<uint64_t>(__knPML4);
    return regs;
}

KEVOS_NSE_3(x64,x86,arch);
