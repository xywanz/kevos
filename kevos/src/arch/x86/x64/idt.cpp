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

#include <string.h>

KEVOS_NSS_3(arch,x86,x64);

InterruptHandler interruptHandlers[IDT::idtSize];

GateDescriptor IDT::items[idtSize];

void IDT::setItem(size_t index,void (*handler)(),uint8_t dpl)
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

void IDT::initialize()
{
    memset(items,0,sizeof(items));

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
    interruptHandlers[FAULT0+0]=faultCppHandler0;
    interruptHandlers[FAULT0+1]=faultCppHandler1;
    interruptHandlers[FAULT0+2]=faultCppHandler2;
    interruptHandlers[FAULT0+3]=faultCppHandler3;
    interruptHandlers[FAULT0+4]=faultCppHandler4;
    interruptHandlers[FAULT0+5]=faultCppHandler5;
    interruptHandlers[FAULT0+6]=faultCppHandler6;
    interruptHandlers[FAULT0+7]=faultCppHandler7;
    interruptHandlers[FAULT0+8]=faultCppHandler8;
    interruptHandlers[FAULT0+9]=faultCppHandler9;
    interruptHandlers[FAULT0+10]=faultCppHandler10;
    interruptHandlers[FAULT0+11]=faultCppHandler11;
    interruptHandlers[FAULT0+12]=faultCppHandler12;
    interruptHandlers[FAULT0+13]=faultCppHandler13;
    interruptHandlers[FAULT0+14]=faultCppHandler14;
    interruptHandlers[FAULT0+15]=faultCppHandler15;
    interruptHandlers[FAULT0+16]=faultCppHandler16;
    interruptHandlers[FAULT0+17]=faultCppHandler17;
    interruptHandlers[FAULT0+18]=faultCppHandler18;
    interruptHandlers[FAULT0+19]=faultCppHandler19;
    interruptHandlers[FAULT0+20]=faultCppHandler20;
    interruptHandlers[FAULT0+21]=faultCppHandler21;
    interruptHandlers[FAULT0+22]=faultCppHandler22;
    interruptHandlers[FAULT0+23]=faultCppHandler23;
    interruptHandlers[FAULT0+24]=faultCppHandler24;
    interruptHandlers[FAULT0+25]=faultCppHandler25;
    interruptHandlers[FAULT0+26]=faultCppHandler26;
    interruptHandlers[FAULT0+27]=faultCppHandler27;
    interruptHandlers[FAULT0+28]=faultCppHandler28;
    interruptHandlers[FAULT0+29]=faultCppHandler29;
    interruptHandlers[FAULT0+30]=faultCppHandler30;
    interruptHandlers[FAULT0+31]=faultCppHandler31;

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
    interruptHandlers[IRQ0+0]=irqCppHandler0;
    interruptHandlers[IRQ0+1]=irqCppHandler1;
    interruptHandlers[IRQ0+2]=irqCppHandler2;
    interruptHandlers[IRQ0+3]=irqCppHandler3;
    interruptHandlers[IRQ0+4]=irqCppHandler4;
    interruptHandlers[IRQ0+5]=irqCppHandler5;
    interruptHandlers[IRQ0+6]=irqCppHandler6;
    interruptHandlers[IRQ0+7]=irqCppHandler7;
    interruptHandlers[IRQ0+8]=irqCppHandler8;
    interruptHandlers[IRQ0+9]=irqCppHandler9;
    interruptHandlers[IRQ0+10]=irqCppHandler10;
    interruptHandlers[IRQ0+11]=irqCppHandler11;
    interruptHandlers[IRQ0+12]=irqCppHandler12;
    interruptHandlers[IRQ0+13]=irqCppHandler13;
    interruptHandlers[IRQ0+14]=irqCppHandler14;
    interruptHandlers[IRQ0+15]=irqCppHandler15;

    setItem(SYSCALL0+0,syscallAsmHandler0,0);
    setItem(SYSCALL0+1,syscallAsmHandler1,0);
    setItem(SYSCALL0+2,syscallAsmHandler2,0);
    setItem(SYSCALL0+3,syscallAsmHandler3,0);
    setItem(SYSCALL0+4,syscallAsmHandler4,0);
    setItem(SYSCALL0+5,syscallAsmHandler5,0);
    setItem(SYSCALL0+6,syscallAsmHandler6,0);
    setItem(SYSCALL0+7,syscallAsmHandler7,0);
    interruptHandlers[SYSCALL0+0]=syscallCppHandler0;
    interruptHandlers[SYSCALL0+1]=syscallCppHandler1;
    interruptHandlers[SYSCALL0+2]=syscallCppHandler2;
    interruptHandlers[SYSCALL0+3]=syscallCppHandler3;
    interruptHandlers[SYSCALL0+4]=syscallCppHandler4;
    interruptHandlers[SYSCALL0+5]=syscallCppHandler5;
    interruptHandlers[SYSCALL0+6]=syscallCppHandler6;
    interruptHandlers[SYSCALL0+7]=syscallCppHandler7;

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


KEVOS_NSE_3(x64,x86,arch);
