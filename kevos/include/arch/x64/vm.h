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

#ifndef _KEVOS_ARCH_X64_VM_H_
#define _KEVOS_ARCH_X64_VM_H_

#include <arch/x64/paging.h>

#define KERNEL_PML4_SIZE		(PML4_SIZE)
#define KERNEL_PDPT_SIZE		(2*PDPT_SIZE)
#define KERNEL_PDT_SIZE 		(2*PDT_SIZE)
#define KERNEL_PT_SIZE 			(8*PT_SIZE)

KEVOS_NSS_3(kevos,arch,x64);

/*内核态的分页*/
extern PML4E __knPML4[KERNEL_PML4_SIZE];
extern PDPTE __knPDPT[KERNEL_PDPT_SIZE];
extern PDTE  __knPDT[KERNEL_PDT_SIZE];
extern PTE   __knPT[KERNEL_PT_SIZE];


KEVOS_NSE_3(x64,arch,kevos);

#endif