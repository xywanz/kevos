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

#define __KERNEL_PML4_NUM			1
#define __KERNEL_PDPT_NUM			1
#define __KERNEL_PDT_NUM 			1
#define __KERNEL_PT_NUM 			16

#define __KERNEL_PML4_SIZE			(__KERNEL_PML4_NUM*__PML4_SIZE)
#define __KERNEL_PDPT_SIZE			(__KERNEL_PDPT_NUM*__PDPT_SIZE)
#define __KERNEL_PDT_SIZE 			(__KERNEL_PDT_NUM*__PDT_SIZE)
#define __KERNEL_PT_SIZE 			(__KERNEL_PT_NUM*__PT_SIZE)

KEVOS_NSS_3(kevos,arch,x64);

/*内核态的分页*/
extern PML4E __knPML4[__KERNEL_PML4_SIZE];
extern PDPTE __knPDPT[__KERNEL_PDPT_SIZE];
extern PDTE  __knPDT [__KERNEL_PDT_SIZE];
extern PTE   __knPT  [__KERNEL_PT_SIZE];

extern uint64_t __pml4PPN;


struct VMemMap
{
	PML4E*  pml4;
	PDPTE*  pdpt;
	PDTE*	pdt;
	PTE*	pt;

	uint64_t pml4PPN;
	uint64_t pdptPPN;
	uint64_t pdtPPN;
	uint64_t ptPPN;

	uint64_t pageSize;

	uint64_t pml4Index;
	uint64_t pdptIndex;
	uint64_t pdtIndex;
	uint64_t ptIndex;		
};


class VMemManager
{
public:
	static VMemMap resolveMap(uint64_t pml4PPN,uint64_t vPagePPN);
	static uint64_t getPhysicalAddrFromPPN(uint64_t ppn,uint64_t pageSize=__PAGE_SIZE)
	{
		return ppn*pageSize;
	}
};


KEVOS_NSE_3(x64,arch,kevos);

#endif