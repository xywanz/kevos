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

#include <cstdlib>

KEVOS_NSS_3(arch,x86,x64);

void irqCppHandler0()
{
    *((unsigned short*)(0xB8000+300))=std::rand();
    arch::common::InterruptManager::sendEndSignal(0);
    switchToContext();
}

void irqCppHandler1()
{
    arch::common::InterruptManager::sendEndSignal(1);
}

void irqCppHandler2()
{
    arch::common::InterruptManager::sendEndSignal(2);
}

void irqCppHandler3()
{
    arch::common::InterruptManager::sendEndSignal(3);
}

void irqCppHandler4()
{
    arch::common::InterruptManager::sendEndSignal(4);
}

void irqCppHandler5()
{
    arch::common::InterruptManager::sendEndSignal(5);
}

void irqCppHandler6()
{
    arch::common::InterruptManager::sendEndSignal(6);
}

void irqCppHandler7()
{
    arch::common::InterruptManager::sendEndSignal(7);
}

void irqCppHandler8()
{
    arch::common::InterruptManager::sendEndSignal(8);
}

void irqCppHandler9()
{
    arch::common::InterruptManager::sendEndSignal(9);
}

void irqCppHandler10()
{
    arch::common::InterruptManager::sendEndSignal(10);
}

void irqCppHandler11()
{
    arch::common::InterruptManager::sendEndSignal(11);
}

void irqCppHandler12()
{
    arch::common::InterruptManager::sendEndSignal(12);
}

void irqCppHandler13()
{
    arch::common::InterruptManager::sendEndSignal(13);
}

void irqCppHandler14()
{
    arch::common::InterruptManager::sendEndSignal(14);
}

void irqCppHandler15()
{
    arch::common::InterruptManager::sendEndSignal(15);
}

KEVOS_NSE_3(x64,x86,arch);
