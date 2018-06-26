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

#include <arch/common/assert.h>

namespace intr::fault
{

void faultCppHandler0()
{
    assert("Error: divided by 0"=="");
    while(1);
}

void faultCppHandler1()
{
    assert("Error: debug exception"=="");
    while(1);
}

void faultCppHandler2()
{
    assert("NMI"=="");
    while(1);
}

void faultCppHandler3()
{
    assert("For debug"=="");
    while(1);
}

void faultCppHandler4()
{
    assert("Error: overflow"=="");
    while(1);
}

void faultCppHandler5()
{
    assert("Bound checking"=="");
    while(1);
}

void faultCppHandler6()
{
    assert("Error: invalid operation code"=="");
    while(1);
}

void faultCppHandler7()
{
    assert("Error: device is not available"=="");
    while(1);
}

void faultCppHandler8()
{
    assert("Error: double error"=="");
    while(1);
}

void faultCppHandler9()
{
    assert("Error: segment out of range in coprocessor"=="");
    while(1);
}

void faultCppHandler10()
{
    assert("Error: invalid tss"=="");
    while(1);
}

void faultCppHandler11()
{
    assert("Error: segment not in memory"=="");
    while(1);
}

void faultCppHandler12()
{
    assert("Error: stack exception"=="");
    while(1);
}

void faultCppHandler13()
{
    assert("Error: general protection"=="");
    while(1);
}

void faultCppHandler14()
{
    assert("Error: page not in memory"=="");
    while(1);
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

} 
