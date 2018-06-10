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

#ifndef _ARCH_X86_X64_KPAGING_H_
#define _ARCH_X86_X64_KPAGING_H_

#include <arch/x86/x64/page_defs.h>

#include <cstddef>

namespace mm::page::kernel
{

constexpr std::size_t pml4Num = 1;
constexpr std::size_t pdptNum = 1;
constexpr std::size_t pdtNum = 1;
constexpr std::size_t ptNum = 32;

constexpr std::size_t pml4Size = pml4EntryNum * pml4Num;
constexpr std::size_t pdptSize = pdptEntryNum * pdptNum;
constexpr std::size_t pdtSize = pdtEntryNum * pdtNum;
constexpr std::size_t ptSize = ptEntryNum * ptNum;

/**
 * @brief 内核态的分页结构表
 */
extern PML4E  pml4[] __aligned__(0x1000);
extern PDPTE  pdpt[] __aligned__(0x1000);
extern PDTE   pdt [] __aligned__(0x1000);
extern PTE    pt  [] __aligned__(0x1000);

}

#endif
