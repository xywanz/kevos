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

#include <cstdlib>

namespace intr::irq
{

void irqCppHandler0()
{
    *((uint16_t*)(0xB8000+310))=((std::rand()%128)<<8)+'k';
    *((uint16_t*)(0xB8000+312))=((std::rand()%128)<<8)+'e';
    *((uint16_t*)(0xB8000+314))=((std::rand()%128)<<8)+'v';
    *((uint16_t*)(0xB8000+316))=((std::rand()%128)<<8)+'o';
    *((uint16_t*)(0xB8000+318))=((std::rand()%128)<<8)+'s';
    InterruptManager::sendEndSignal(0);

    multitask::ProcessManager::switchToNext();
    switchToContext();
}

void irqCppHandler1()
{
    InterruptManager::sendEndSignal(1);
}

void irqCppHandler2()
{
    InterruptManager::sendEndSignal(2);
}

void irqCppHandler3()
{
    InterruptManager::sendEndSignal(3);
}

void irqCppHandler4()
{
    InterruptManager::sendEndSignal(4);
}

void irqCppHandler5()
{
    InterruptManager::sendEndSignal(5);
}

void irqCppHandler6()
{
    InterruptManager::sendEndSignal(6);
}

void irqCppHandler7()
{
    InterruptManager::sendEndSignal(7);
}

void irqCppHandler8()
{
    InterruptManager::sendEndSignal(8);
}

void irqCppHandler9()
{
    InterruptManager::sendEndSignal(9);
}

void irqCppHandler10()
{
    InterruptManager::sendEndSignal(10);
}

void irqCppHandler11()
{
    InterruptManager::sendEndSignal(11);
}

void irqCppHandler12()
{
    InterruptManager::sendEndSignal(12);
}

void irqCppHandler13()
{
    InterruptManager::sendEndSignal(13);
}

void irqCppHandler14()
{
    InterruptManager::sendEndSignal(14);
}

void irqCppHandler15()
{
    InterruptManager::sendEndSignal(15);
}

}
