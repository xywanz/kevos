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

#ifndef _KEVOS_ARCH_COMMON_ATADRIVER_H_
#define _KEVOS_ARCH_COMMON_ATADRIVER_H_

#include <arch/common/types.h>

#include <cstddef>

namespace arch::x86::common
{

class ATADriver
{
public:

    std::size_t readSectors(std::size_t start,std::size_t count,void* dst,std::size_t& readCount);

    std::size_t writeSectors(std::size_t start,std::size_t count,const void* src,std::size_t& writeCount);

};

}   // end of namespace arch::x86::common

#endif
