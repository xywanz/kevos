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

#include <arch/x86_64/x64/vm.h>

KEVOS_NSS_4(kevos,arch,x86_64,x64);


PML4E 	__knPML4[__KERNEL_PML4_SIZE] 	__aligned__(0x1000);
PDPTE 	__knPDPT[__KERNEL_PDPT_SIZE]	__aligned__(0x1000);
PDTE  	__knPDT [__KERNEL_PDT_SIZE] 	__aligned__(0x1000);
PTE   	__knPT  [__KERNEL_PT_SIZE] 		__aligned__(0x1000);


bool VirtualMemory::mapPage(uint64_t vPagePPN,uint64_t pPagePPN,uint64_t userAccessable,uint64_t pageSize)
{
	
}

bool VirtualMemory::unmapPage(uint64_t vPagePPN)
{
	return true;
}

VMemMap VirtualMemory::resolveMap(uint64_t pml4PPN,uint64_t vPagePPN)
{
	VMemMap vmm;

	vmm.ptIndex=vPagePPN;
	vmm.pdtIndex=vmm.ptIndex/__PT_SIZE;
	vmm.pdptIndex=vmm.pdtIndex/__PDT_SIZE;
	vmm.pml4Index=vmm.pdptIndex/__PDPT_SIZE;

	vmm.ptIndex%=__PT_SIZE;
	vmm.pdtIndex%=__PDT_SIZE;
	vmm.pdptIndex%=__PDPT_SIZE;
	vmm.pml4Index%=__PML4_SIZE;

	vmm.pml4PPN=pml4PPN;
	vmm.pml4=reinterpret_cast<PML4E*>(getAddressFromPPN(pml4PPN));

	vmm.pdptPPN=vmm.pml4[vmm.pml4Index].physicalPageNum;
	vmm.pdpt=reinterpret_cast<PDPTE*>(getAddressFromPPN(vmm.pdptPPN));

	vmm.pdtPPN=vmm.pdpt[vmm.pdptIndex].physicalPageNum;
	vmm.pdt=reinterpret_cast<PDTE*>(getAddressFromPPN(vmm.pdtPPN));

	vmm.ptPPN=vmm.pdt[vmm.pdtIndex].physicalPageNum;
	vmm.pt=reinterpret_cast<PTE*>(getAddressFromPPN(vmm.ptPPN));
	
	vmm.pageSize=__PAGE_SIZE;

	// if(vmm.pml4[vmm.pml4Index].present)
	// {
	// 	vmm.pdptPPN=vmm.pml4[vmm.pml4Index].physicalPageNum;
	// 	vmm.pdpt=reinterpret_cast<PDPTE*>(getPhysicalAddrFromPPN(vmm.pdptPPN));

	// 	if(vmm.pdpt[vmm.pdptIndex].present)
	// 	{
	// 		vmm.pdtPPN=vmm.pdpt[vmm.pdptIndex].physicalPageNum;
	// 		vmm.pdt=reinterpret_cast<PDTE*>(getPhysicalAddrFromPPN(vmm.pdtPPN));

	// 		if(vmm.pdt[vmm.pdtIndex].present)
	// 		{
	// 			vmm.ptPPN=vmm.pdt[vmm.pdtIndex].physicalPageNum;
	// 			vmm.pt=reinterpret_cast<PTE*>(getPhysicalAddrFromPPN(vmm.ptPPN));
	// 			vmm.pageSize=__PAGE_SIZE;
	// 		}
	// 	}
	// }

	return vmm;
}


KEVOS_NSE_4(x64,x86_64,arch,kevos);
