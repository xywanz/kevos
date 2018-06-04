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

#include <arch/x86/x64/interrupt.h>

namespace arch::x86::x64
{

void faultCppHandler0()
{
    *((unsigned short*)0xB8000+1000)=0x7575;
}

void faultCppHandler1()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler2()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler3()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler4()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler5()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler6()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler7()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler8()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler9()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler10()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler11()
{
    *((unsigned short*)0xB8000+1000)=0x7575;
}

void faultCppHandler12()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler13()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler14()
{
    *((unsigned short*)0xB8000+1000)=0x7575;
}

void faultCppHandler15()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler16()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler17()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler18()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler19()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler20()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler21()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler22()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler23()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler24()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler25()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler26()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler27()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler28()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler29()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler30()
{
    __asm__ __volatile__("hlt");
}

void faultCppHandler31()
{
    __asm__ __volatile__("hlt");
}

}   // end of namespace arch::x86::x64
