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

IRQHandler irqHandlers[16];

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

    irqHandlers[0]=irqCppHandler0;
    irqHandlers[1]=irqCppHandler1;
    irqHandlers[2]=irqCppHandler2;
    irqHandlers[3]=irqCppHandler3;
    irqHandlers[4]=irqCppHandler4;
    irqHandlers[5]=irqCppHandler5;
    irqHandlers[6]=irqCppHandler6;
    irqHandlers[7]=irqCppHandler7;
    irqHandlers[8]=irqCppHandler8;
    irqHandlers[9]=irqCppHandler9;
    irqHandlers[10]=irqCppHandler10;
    irqHandlers[11]=irqCppHandler11;
    irqHandlers[12]=irqCppHandler12;
    irqHandlers[13]=irqCppHandler13;
    irqHandlers[14]=irqCppHandler14;
    irqHandlers[15]=irqCppHandler15;

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
