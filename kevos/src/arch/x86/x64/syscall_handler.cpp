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

#include <cstdlib>

namespace intr::syscall
{

void syscallCppHandler0()
{
    *((unsigned short*)0xB8000+240)=0x7575;
}

void syscallCppHandler1()
{

}

void syscallCppHandler2()
{

}

void syscallCppHandler3()
{

}

void syscallCppHandler4()
{

}

void syscallCppHandler5()
{

}
void syscallCppHandler6()
{

}

void syscallCppHandler7()
{

}

}
