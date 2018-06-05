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

#include <arch/x86/x64/paging.h>

#include <cstddef>

namespace arch::x86::x64
{

/**
 * @brief 内核中各分页结构表的大小
 */
#define __KERNEL_PML4_NUM           1
#define __KERNEL_PDPT_NUM           1
#define __KERNEL_PDT_NUM            1
#define __KERNEL_PT_NUM             32

/**
 * @brief 内核中各分页结构表项的数量
 */
#define __KERNEL_PML4_SIZE          (__KERNEL_PML4_NUM*__PML4_SIZE)
#define __KERNEL_PDPT_SIZE          (__KERNEL_PDPT_NUM*__PDPT_SIZE)
#define __KERNEL_PDT_SIZE           (__KERNEL_PDT_NUM*__PDT_SIZE)
#define __KERNEL_PT_SIZE            (__KERNEL_PT_NUM*__PT_SIZE)

/**
 * @brief 内核态的分页结构表
 */

class KernelPageFrame
{
public:
    constexpr static std::size_t pml4Size = 512;
    constexpr static std::size_t pdptSize = 512;
    constexpr static std::size_t pdtSize = 512;
    constexpr static std::size_t ptSize = 512*32;

    static PML4E  pml4[];
    static PDPTE  pdpt[];
    static PDTE   pdt [];
    static PTE    pt  [];
};

}
