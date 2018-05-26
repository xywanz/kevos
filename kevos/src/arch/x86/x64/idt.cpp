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

KEVOS_NSS_3(arch,x86,x64);

GateDescriptor IDT::items[idtSize];

void IDT::setItem(size_t index,void (*handler)())
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
	item->dpl=0;
	item->present=1;
	item->reserved=0;
}

void IDT::initialize()
{


	struct
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
