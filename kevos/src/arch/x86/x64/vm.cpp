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

#include <arch/x86/x64/vm.h>
#include <kernel/mm/page_mgr.h>
#include <string.h>

KEVOS_NSS_3(arch,x86,x64);

PML4E 	__knPML4[__KERNEL_PML4_SIZE] 	__aligned__(0x1000);
PDPTE 	__knPDPT[__KERNEL_PDPT_SIZE]	__aligned__(0x1000);
PDTE  	__knPDT [__KERNEL_PDT_SIZE] 	__aligned__(0x1000);
PTE   	__knPT  [__KERNEL_PT_SIZE] 		__aligned__(0x1000);

VirtualMemory::VirtualMemory()
{
	m_pml4PPN=kernel::mm::PageManager::allocate();
	memset((void*)getAddressFromPPN(m_pml4PPN),0,__PAGE_SIZE);
}

bool VirtualMemory::mapPage(uint64_t vPagePPN,uint64_t pPagePPN,uint64_t userAccessable,uint64_t pageSize)
{
	VMemMap vmm=resolveMap(vPagePPN);
	if(!vmm.pml4[vmm.pml4Index].present)
	{
		uint64_t pdptPPN=kernel::mm::PageManager::allocate(pageSize);
		setPagingEntry(vmm.pml4,vmm.pml4Index,pdptPPN,1,1,1);
		vmm.pdpt=reinterpret_cast<PDPTE*>(getAddressFromPPN(pdptPPN));
	}
	if(!vmm.pdpt[vmm.pdptIndex].present)
	{
		uint64_t pdtPPN=kernel::mm::PageManager::allocate(pageSize);
		setPagingEntry(vmm.pdpt,vmm.pdptIndex,pdtPPN,1,1,1);
		vmm.pdt=reinterpret_cast<PDTE*>(getAddressFromPPN(pdtPPN));
	}
	if(!vmm.pdt[vmm.pdtIndex].present)
	{
		uint64_t ptPPN=kernel::mm::PageManager::allocate(pageSize);
		setPagingEntry(vmm.pdt,vmm.pdtIndex,ptPPN,1,1,1);
		vmm.pt=reinterpret_cast<PTE*>(getAddressFromPPN(ptPPN));
	}
	setPagingEntry(vmm.pt,vmm.ptIndex,pPagePPN,1,1,1);
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

	vmm.pdptPPN=vmm.pdtPPN=vmm.ptPPN=0;
	vmm.pdpt=nullptr;
	vmm.pdt=nullptr;
	vmm.pt=nullptr;
	
	vmm.pageSize=__PAGE_SIZE;

	if(vmm.pml4[vmm.pml4Index].present)
	{
		vmm.pdptPPN=vmm.pml4[vmm.pml4Index].physicalPageNum;
		vmm.pdpt=reinterpret_cast<PDPTE*>(getAddressFromPPN(vmm.pdptPPN));

		if(vmm.pdpt[vmm.pdptIndex].present)
		{
			vmm.pdtPPN=vmm.pdpt[vmm.pdptIndex].physicalPageNum;
			vmm.pdt=reinterpret_cast<PDTE*>(getAddressFromPPN(vmm.pdtPPN));

			if(vmm.pdt[vmm.pdtIndex].present)
			{
				vmm.ptPPN=vmm.pdt[vmm.pdtIndex].physicalPageNum;
				vmm.pt=reinterpret_cast<PTE*>(getAddressFromPPN(vmm.ptPPN));
			}
		}
	}

	return vmm;
}

template<class T>
void VirtualMemory::setPagingEntry(T* entries,size_t index,size_t ppn,
		uint64_t isToClear,uint64_t userAccessable,uint64_t writable)
{
	if(isToClear)
		memset((void*)getAddressFromPPN(ppn),0,__PAGE_SIZE);
	entries[index].physicalPageNum=ppn;
	entries[index].userAccessable=userAccessable;
	entries[index].writable=writable;
	entries[index].present=1;
}

KEVOS_NSE_3(x64,x86,arch);
