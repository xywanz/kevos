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
#include <arch/x86/common/i8259a.h>

KEVOS_NSS_3(arch,x86,x64);

extern "C"
{
	void irqCppHandler0()
	{
		
	}

	void irqCppHandler1()
	{

	}
}

KEVOS_NSE_3(x64,x86,arch);



KEVOS_NSS_2(arch,common);


void InterruptManager::initialize()
{
	x86::common::I8259A::initialize();
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
  	if(freq < (uint32_t)(1193180. / (1 << 16) + 1)) {
  	  	divisor = 0;
  	} else {
  	  divisor = (uint16_t)(1193180 / freq);
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

KEVOS_NSE_2(common,arch);
