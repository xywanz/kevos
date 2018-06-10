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

#include <arch/x86/x64/idt.h>
#include <arch/x86/x64/gdt.h>
#include <arch/x86/x64/interrupt.h>

#include <cstring>

extern "C" {
    desc::idt::InterruptHandler interruptHandlers[desc::idt::idtSize];
}

namespace desc::idt
{

GateDescriptor items[idtSize];

void setItem(std::size_t index,InterruptHandler handler,uint8_t dpl)
{
    GateDescriptor* item=items+index;
    uint64_t h=reinterpret_cast<uint64_t>(handler);
    item->offsetLow=h&0xFFFF;
    item->offsetMid=(h>>16)&0xFFFF;
    item->offsetHigh=(h>>32)&0xFFFFFFFF;
    item->codeSelector=__KERNEL_CS;
    item->ist=0;
    item->zero1=0;
    item->zero2=0;
    item->type=GATE_TYPE_INTERRUPT;
    item->dpl=dpl;
    item->present=1;
    item->reserved=0;
}

void initialize()
{
    std::memset(items,0,sizeof(items));

    setItem(FAULT0+0,faultAsmHandler0,0);
    setItem(FAULT0+1,faultAsmHandler1,0);
    setItem(FAULT0+2,faultAsmHandler2,0);
    setItem(FAULT0+3,faultAsmHandler3,0);
    setItem(FAULT0+4,faultAsmHandler4,0);
    setItem(FAULT0+5,faultAsmHandler5,0);
    setItem(FAULT0+6,faultAsmHandler6,0);
    setItem(FAULT0+7,faultAsmHandler7,0);
    setItem(FAULT0+8,faultAsmHandler8,0);
    setItem(FAULT0+9,faultAsmHandler9,0);
    setItem(FAULT0+10,faultAsmHandler10,0);
    setItem(FAULT0+11,faultAsmHandler11,0);
    setItem(FAULT0+12,faultAsmHandler12,0);
    setItem(FAULT0+13,faultAsmHandler13,0);
    setItem(FAULT0+14,faultAsmHandler14,0);
    setItem(FAULT0+15,faultAsmHandler15,0);
    setItem(FAULT0+16,faultAsmHandler16,0);
    setItem(FAULT0+17,faultAsmHandler17,0);
    setItem(FAULT0+18,faultAsmHandler18,0);
    setItem(FAULT0+19,faultAsmHandler19,0);
    setItem(FAULT0+20,faultAsmHandler20,0);
    setItem(FAULT0+21,faultAsmHandler21,0);
    setItem(FAULT0+22,faultAsmHandler22,0);
    setItem(FAULT0+23,faultAsmHandler23,0);
    setItem(FAULT0+24,faultAsmHandler24,0);
    setItem(FAULT0+25,faultAsmHandler25,0);
    setItem(FAULT0+26,faultAsmHandler26,0);
    setItem(FAULT0+27,faultAsmHandler27,0);
    setItem(FAULT0+28,faultAsmHandler28,0);
    setItem(FAULT0+29,faultAsmHandler29,0);
    setItem(FAULT0+30,faultAsmHandler30,0);
    setItem(FAULT0+31,faultAsmHandler31,0);
    registerCallback(FAULT0+0,intr::fault::faultCppHandler0);
    registerCallback(FAULT0+1,intr::fault::faultCppHandler1);
    registerCallback(FAULT0+2,intr::fault::faultCppHandler2);
    registerCallback(FAULT0+3,intr::fault::faultCppHandler3);
    registerCallback(FAULT0+4,intr::fault::faultCppHandler4);
    registerCallback(FAULT0+5,intr::fault::faultCppHandler5);
    registerCallback(FAULT0+6,intr::fault::faultCppHandler6);
    registerCallback(FAULT0+7,intr::fault::faultCppHandler7);
    registerCallback(FAULT0+8,intr::fault::faultCppHandler8);
    registerCallback(FAULT0+9,intr::fault::faultCppHandler9);
    registerCallback(FAULT0+10,intr::fault::faultCppHandler10);
    registerCallback(FAULT0+11,intr::fault::faultCppHandler11);
    registerCallback(FAULT0+12,intr::fault::faultCppHandler12);
    registerCallback(FAULT0+13,intr::fault::faultCppHandler13);
    registerCallback(FAULT0+14,intr::fault::faultCppHandler14);
    registerCallback(FAULT0+15,intr::fault::faultCppHandler15);
    registerCallback(FAULT0+16,intr::fault::faultCppHandler16);
    registerCallback(FAULT0+17,intr::fault::faultCppHandler17);
    registerCallback(FAULT0+18,intr::fault::faultCppHandler18);
    registerCallback(FAULT0+19,intr::fault::faultCppHandler19);
    registerCallback(FAULT0+20,intr::fault::faultCppHandler20);
    registerCallback(FAULT0+21,intr::fault::faultCppHandler21);
    registerCallback(FAULT0+22,intr::fault::faultCppHandler22);
    registerCallback(FAULT0+23,intr::fault::faultCppHandler23);
    registerCallback(FAULT0+24,intr::fault::faultCppHandler24);
    registerCallback(FAULT0+25,intr::fault::faultCppHandler25);
    registerCallback(FAULT0+26,intr::fault::faultCppHandler26);
    registerCallback(FAULT0+27,intr::fault::faultCppHandler27);
    registerCallback(FAULT0+28,intr::fault::faultCppHandler28);
    registerCallback(FAULT0+29,intr::fault::faultCppHandler29);
    registerCallback(FAULT0+30,intr::fault::faultCppHandler30);
    registerCallback(FAULT0+31,intr::fault::faultCppHandler31);

    setItem(IRQ0+0,irqAsmHandler0,0);
    setItem(IRQ0+1,irqAsmHandler1,0);
    setItem(IRQ0+2,irqAsmHandler2,0);
    setItem(IRQ0+3,irqAsmHandler3,0);
    setItem(IRQ0+4,irqAsmHandler4,0);
    setItem(IRQ0+5,irqAsmHandler5,0);
    setItem(IRQ0+6,irqAsmHandler6,0);
    setItem(IRQ0+7,irqAsmHandler7,0);
    setItem(IRQ0+8,irqAsmHandler8,0);
    setItem(IRQ0+9,irqAsmHandler9,0);
    setItem(IRQ0+10,irqAsmHandler10,0);
    setItem(IRQ0+11,irqAsmHandler11,0);
    setItem(IRQ0+12,irqAsmHandler12,0);
    setItem(IRQ0+13,irqAsmHandler13,0);
    setItem(IRQ0+14,irqAsmHandler14,0);
    setItem(IRQ0+15,irqAsmHandler15,0);
    registerCallback(IRQ0+0,intr::irq::irqCppHandler0);
    registerCallback(IRQ0+1,intr::irq::irqCppHandler1);
    registerCallback(IRQ0+2,intr::irq::irqCppHandler2);
    registerCallback(IRQ0+3,intr::irq::irqCppHandler3);
    registerCallback(IRQ0+4,intr::irq::irqCppHandler4);
    registerCallback(IRQ0+5,intr::irq::irqCppHandler5);
    registerCallback(IRQ0+6,intr::irq::irqCppHandler6);
    registerCallback(IRQ0+7,intr::irq::irqCppHandler7);
    registerCallback(IRQ0+8,intr::irq::irqCppHandler8);
    registerCallback(IRQ0+9,intr::irq::irqCppHandler9);
    registerCallback(IRQ0+10,intr::irq::irqCppHandler10);
    registerCallback(IRQ0+11,intr::irq::irqCppHandler11);
    registerCallback(IRQ0+12,intr::irq::irqCppHandler12);
    registerCallback(IRQ0+13,intr::irq::irqCppHandler13);
    registerCallback(IRQ0+14,intr::irq::irqCppHandler14);
    registerCallback(IRQ0+15,intr::irq::irqCppHandler15);

    setItem(SYSCALL0+0,syscallAsmHandler0,0);
    setItem(SYSCALL0+1,syscallAsmHandler1,0);
    setItem(SYSCALL0+2,syscallAsmHandler2,0);
    setItem(SYSCALL0+3,syscallAsmHandler3,0);
    setItem(SYSCALL0+4,syscallAsmHandler4,0);
    setItem(SYSCALL0+5,syscallAsmHandler5,0);
    setItem(SYSCALL0+6,syscallAsmHandler6,0);
    setItem(SYSCALL0+7,syscallAsmHandler7,0);
    registerCallback(SYSCALL0+0,intr::syscall::syscallCppHandler0);
    registerCallback(SYSCALL0+1,intr::syscall::syscallCppHandler1);
    registerCallback(SYSCALL0+2,intr::syscall::syscallCppHandler2);
    registerCallback(SYSCALL0+3,intr::syscall::syscallCppHandler3);
    registerCallback(SYSCALL0+4,intr::syscall::syscallCppHandler4);
    registerCallback(SYSCALL0+5,intr::syscall::syscallCppHandler5);
    registerCallback(SYSCALL0+6,intr::syscall::syscallCppHandler6);
    registerCallback(SYSCALL0+7,intr::syscall::syscallCppHandler7);

    struct __packed__
    {
        uint16_t limit;
        uint64_t address;
    }idtr={
        sizeof(items)-1,
        reinterpret_cast<uint64_t>(items)
    };
    __asm__ __volatile__("lidt %[idtr]" : : [idtr]"m"(idtr));
}

void registerCallback(std::size_t intNum,InterruptHandler handler)
{
    interruptHandlers[intNum]=handler;
}

}
