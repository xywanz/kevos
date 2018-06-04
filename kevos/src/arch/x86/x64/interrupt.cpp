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

#include <arch/common/interrupt.h>
#include <arch/x86/x64/interrupt.h>
#include <arch/x86/x64/process.h>
#include <arch/x86/x64/idt.h>
#include <arch/x86/common/i8259a.h>

namespace arch::x86::x64
{

void saveProcessRegisters(char* base)
{
    auto regs=ProcessManager::current()->registers();
    auto ssregs=reinterpret_cast<SoftwareSavedRegisters*>(base);
    regs->rax=ssregs->rax;
    regs->rbx=ssregs->rbx;
    regs->rcx=ssregs->rcx;
    regs->rdx=ssregs->rdx;
    regs->rsi=ssregs->rsi;
    regs->rdi=ssregs->rdi;
    regs->rbp=ssregs->rbp;
    regs->r8=ssregs->r8;
    regs->r9=ssregs->r9;
    regs->r10=ssregs->r10;
    regs->r11=ssregs->r11;
    regs->r12=ssregs->r12;
    regs->r13=ssregs->r13;
    regs->r14=ssregs->r14;
    regs->r15=ssregs->r15;
    regs->ds=ssregs->ds;
    regs->es=ssregs->es;
    auto hsregs=reinterpret_cast<HardwareSavedRegisters*>(base+sizeof(SoftwareSavedRegisters));
    regs->rip=hsregs->rip;
    regs->cs=hsregs->cs;
    regs->rflags=hsregs->rflags;
    regs->rsp=hsregs->rsp;
    regs->ss=hsregs->ss;
}

void switchToContext()
{
    auto regs=ProcessManager::current()->registers();
    // TSS::tss.rsp0=regs->rsp0;
    __asm__ __volatile__("movq %[cr3],%%cr3" : : [cr3]"r"(regs->cr3));
    __asm__ __volatile__("pushq %[ss]" : : [ss]"m"(regs->ss));
    __asm__ __volatile__("pushq %[rsp]" : : [rsp]"m"(regs->rsp));
    __asm__ __volatile__("pushq %[rflags]" : : [rflags]"m"(regs->rflags));
    __asm__ __volatile__("pushq %[cs]" : : [cs]"m"(regs->cs));
    __asm__ __volatile__("pushq %[rip]" : : [rip]"m"(regs->rip));
    __asm__ __volatile__("movw %[ds],%%ds" : : [ds]"r"(regs->ds));
    __asm__ __volatile__("movw %[es],%%es" : : [es]"r"(regs->es));
    __asm__ __volatile__("movw %[fs],%%fs" : : [fs]"r"(regs->fs));
    __asm__ __volatile__("movw %[gs],%%gs" : : [gs]"r"(regs->gs));
    __asm__ __volatile__("movq %[rax],%%rax" : : [rax]"m"(regs->rax));
    __asm__ __volatile__("movq %[rbx],%%rbx" : : [rbx]"m"(regs->rbx));
    __asm__ __volatile__("movq %[rcx],%%rcx" : : [rcx]"m"(regs->rcx));
    __asm__ __volatile__("movq %[rdx],%%rdx" : : [rdx]"m"(regs->rdx));
    __asm__ __volatile__("movq %[rsi],%%rsi" : : [rsi]"m"(regs->rsi));
    __asm__ __volatile__("movq %[rdi],%%rdi" : : [rdi]"m"(regs->rdi));
    __asm__ __volatile__("movq %[rbp],%%rbp" : : [rbp]"m"(regs->rbp));
    __asm__ __volatile__("movq %[r8],%%r8" : : [r8]"m"(regs->r8));
    __asm__ __volatile__("movq %[r9],%%r9" : : [r9]"m"(regs->r9));
    __asm__ __volatile__("movq %[r10],%%r10" : : [r10]"m"(regs->r10));
    __asm__ __volatile__("movq %[r11],%%r11" : : [r11]"m"(regs->r11));
    __asm__ __volatile__("movq %[r12],%%r12" : : [r12]"m"(regs->r12));
    __asm__ __volatile__("movq %[r13],%%r13" : : [r13]"m"(regs->r13));
    __asm__ __volatile__("movq %[r14],%%r14" : : [r14]"m"(regs->r14));
    __asm__ __volatile__("movq %[r15],%%r15" : : [r15]"m"(regs->r15));
    __asm__ __volatile__("iretq");
}

}   // end of namespace arch::x86::x64






namespace arch::common
{


void InterruptManager::initialize()
{
    x86::common::I8259A::initialize();
    x86::x64::IDT::initialize();
}

void InterruptManager::enableInterrupts()
{
    __asm__ __volatile__("sti");
}

void InterruptManager::disableInterrupts()
{
    __asm__ __volatile__("cli");
}

void InterruptManager::sendEndSignal(uint16_t num)
{
    x86::common::I8259A::sendEOI(num);
}

void InterruptManager::enableTimer()
{
    x86::common::I8259A::enableIRQ(0);
}

void InterruptManager::disableTimer()
{
    x86::common::I8259A::disableIRQ(0);
}

void InterruptManager::setTimerFrequency(uint32_t freq)
{
    uint16_t divisor;
    if(freq < static_cast<uint32_t>(1193180. / (1 << 16) + 1)) {
        divisor = 0;
    } else {
      divisor = static_cast<uint32_t>(1193180 / freq);
    }
    x86::common::outportb(0x43, 0x36);
    x86::common::outportb(0x40, divisor & 0xFF);
    x86::common::outportb(0x40, divisor >> 8);
}

void InterruptManager::enableKeyboard()
{
    x86::common::I8259A::enableIRQ(1);
}

void InterruptManager::disableKeyboard()
{
    x86::common::I8259A::disableIRQ(1);
}

}   // end of namespace arch::common
