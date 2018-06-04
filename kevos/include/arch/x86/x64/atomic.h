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

#ifndef _KEVOS_ARCH_X86_X64_ATOMIC_H_
#define _KEVOS_ARCH_X86_X64_ATOMIC_H_

#include <sys/types.h>

namespace arch::x86::x64
{

class AtomicOps
{
public:

    template<class T1,class T2>
    static T1 add(T1& lhs,T2 rhs)
    {
        T1 ret=rhs;
        __asm__ __volatile__("xadd %0,%1" : "=a"(ret),"=m"(lhs) : "a"(ret));
        return ret;
    }
    
};

}   // end of namespace arch::x86::x64

#endif
