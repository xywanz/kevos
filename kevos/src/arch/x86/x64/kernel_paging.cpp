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

#include <arch/x86/x64/kernel_paging.h>

namespace arch::x86::x64
{

PML4E  KernelPageFrame::pml4[pml4Size] __aligned__(0x1000);
PDPTE  KernelPageFrame::pdpt[pdptSize] __aligned__(0x1000);
PDTE   KernelPageFrame::pdt[pdtSize]   __aligned__(0x1000);
PTE    KernelPageFrame::pt[ptSize]     __aligned__(0x1000);

}
