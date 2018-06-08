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

#include <arch/x86/x64/tss.h>
#include <kernel/mm/mem_layout.h>

#include <cstring>

namespace arch::x86::x64
{

TaskStateSegment TSS::tss;

void TSS::initialize()
{
    std::memset(&tss,0,sizeof(TaskStateSegment));
    tss.ist0=reinterpret_cast<uint64_t>(&kstack_start_address);
    tss.rsp0=(uint64_t)(&kstack_start_address);
}

}   // end of namespace arch::x86::x64
