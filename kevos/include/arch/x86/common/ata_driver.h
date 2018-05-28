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

KEVOS_NSS_3(arch,x86,common);

class ATADriver
{
public:

    size_t readSectors(size_t start,size_t count,void* dst,size_t& readCount);

    size_t writeSectors(size_t start,size_t count,const void* src,size_t& writeCount);

};

KEVOS_NSE_3(common,x86,arch);

#endif
