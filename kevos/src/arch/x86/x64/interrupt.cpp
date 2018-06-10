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
#include <arch/x86/x64/tss.h>
#include <arch/x86/common/i8259a.h>


void saveProcessRegisters(char* base)
{
    auto regs=multitask::ProcessManager::current()->registers();
    auto ssregs=reinterpret_cast<intr::SoftwareSavedRegisters*>(base);
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
    auto hsregs=reinterpret_cast<intr::HardwareSavedRegisters*>(base+sizeof(intr::SoftwareSavedRegisters));
    regs->rip=hsregs->rip;
    regs->cs=hsregs->cs;
    regs->rflags=hsregs->rflags;
    regs->rsp=hsregs->rsp;
    regs->ss=hsregs->ss;
}

void switchToContext()
{
    auto regs=multitask::ProcessManager::current()->registers();
    // TSS::tss.rsp0=regs->rsp;
    __asm__ ("movq %[cr3],%%cr3" : : [cr3]"r"(regs->cr3));
    __asm__ ("pushq %[ss]" : : [ss]"m"(regs->ss));
    __asm__ ("pushq %[rsp]" : : [rsp]"m"(regs->rsp));
    __asm__ ("pushq %[rflags]" : : [rflags]"m"(regs->rflags));
    __asm__ ("pushq %[cs]" : : [cs]"m"(regs->cs));
    __asm__ ("pushq %[rip]" : : [rip]"m"(regs->rip));
    __asm__ ("movw %[ds],%%ds" : : [ds]"r"(regs->ds));
    __asm__ ("movw %[es],%%es" : : [es]"r"(regs->es));
    __asm__ ("movq %[rbx],%%rbx" : : [rbx]"m"(regs->rbx));
    __asm__ ("movq %[rcx],%%rcx" : : [rcx]"m"(regs->rcx));
    __asm__ ("movq %[rdx],%%rdx" : : [rdx]"m"(regs->rdx));
    __asm__ ("movq %[rsi],%%rsi" : : [rsi]"m"(regs->rsi));
    __asm__ ("movq %[rdi],%%rdi" : : [rdi]"m"(regs->rdi));
    __asm__ ("movq %[r8],%%r8" : : [r8]"m"(regs->r8));
    __asm__ ("movq %[r9],%%r9" : : [r9]"m"(regs->r9));
    __asm__ ("movq %[r10],%%r10" : : [r10]"m"(regs->r10));
    __asm__ ("movq %[r11],%%r11" : : [r11]"m"(regs->r11));
    __asm__ ("movq %[r12],%%r12" : : [r12]"m"(regs->r12));
    __asm__ ("movq %[r13],%%r13" : : [r13]"m"(regs->r13));
    __asm__ ("movq %[r14],%%r14" : : [r14]"m"(regs->r14));
    __asm__ ("movq %[r15],%%r15" : : [r15]"m"(regs->r15));
    __asm__ ("movq %[rax],%%rax" : : [rax]"m"(regs->rax));
    __asm__ __volatile__("pushq %rax");
    __asm__ ("movq %[rbp],%%rbp" : : [rbp]"m"(regs->rbp));
    __asm__ __volatile__("popq %rax");
    __asm__ __volatile__("iretq");
}



namespace intr
{


void InterruptManager::initialize()
{
    I8259A::initialize();
    desc::idt::initialize();
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
    I8259A::sendEOI(num);
}

void InterruptManager::enableTimer()
{
    I8259A::enableIRQ(0);
}

void InterruptManager::disableTimer()
{
    I8259A::disableIRQ(0);
}

void InterruptManager::setTimerFrequency(uint32_t freq)
{
    uint16_t divisor;
    if(freq < static_cast<uint32_t>(1193180. / (1 << 16) + 1)) {
        divisor = 0;
    } else {
      divisor = static_cast<uint32_t>(1193180 / freq);
    }
    io::outportb(0x43, 0x36);
    io::outportb(0x40, divisor & 0xFF);
    io::outportb(0x40, divisor >> 8);
}

void InterruptManager::enableKeyboard()
{
    I8259A::enableIRQ(1);
}

void InterruptManager::disableKeyboard()
{
    I8259A::disableIRQ(1);
}

}
