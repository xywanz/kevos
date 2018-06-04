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

#include <cstring>

namespace arch::x86::x64
{

PML4E  KernelPageFrame::pml4[pml4Size] __aligned__(0x1000);
PDPTE  KernelPageFrame::pdpt[pdptSize] __aligned__(0x1000);
PDTE   KernelPageFrame::pdt[pdtSize]   __aligned__(0x1000);
PTE    KernelPageFrame::pt[ptSize]     __aligned__(0x1000);

VirtualMemory::VirtualMemory()
{
    m_pml4PPN=kernel::mm::PageManager::allocate();
    std::memset((void*)getAddressFromPPN(m_pml4PPN),0,__PAGE_SIZE);
}

VirtualMemory::~VirtualMemory()
{
    PML4E* pml4=reinterpret_cast<PML4E*>(getAddressFromPPN(m_pml4PPN));
    for(size_t pml4i=0;pml4i<__PML4_SIZE;++pml4i)
    {
        if(pml4[pml4i].present)
        {
            PDPTE* pdpt=reinterpret_cast<PDPTE*>(getAddressFromPPN(pml4[pml4i].physicalPageNum));
            for(size_t pdpti=0;pdpti<__PDPT_SIZE;++pdpti)
            {
                if(pdpt[pdpti].present)
                {
                    PDTE* pdt=reinterpret_cast<PDTE*>(getAddressFromPPN(pdpt[pdpti].physicalPageNum));
                    for(size_t pdti=0;pdti<__PDT_SIZE;++pdti)
                    {
                        if(pdt[pdti].present)
                        {
                            PTE* pt=reinterpret_cast<PTE*>(getAddressFromPPN(pdt[pdti].physicalPageNum));
                            for(size_t pti=0;pti<__PT_SIZE;++pti)
                            {
                                if(pt[pti].present)
                                {
                                    kernel::mm::PageManager::deallocate(pt[pti].physicalPageNum);
                                }
                            }
                            kernel::mm::PageManager::deallocate(pdt[pdti].physicalPageNum);
                        }
                    }
                    kernel::mm::PageManager::deallocate(pdpt[pdpti].physicalPageNum);
                }
            }
            kernel::mm::PageManager::deallocate(pml4[pml4i].physicalPageNum);
        }
    }
    kernel::mm::PageManager::deallocate(m_pml4PPN);
}

void VirtualMemory::mapPage(uint64_t vpn,uint64_t ppn,uint64_t userAccessable,uint64_t pageSize)
{
    VMemMap vmm=resolveMap(vpn);
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
    setPagingEntry(vmm.pt,vmm.ptIndex,ppn,1,1,1);
}

void VirtualMemory::fillPageFrame(uint64_t vpn,uint64_t userAccessable,uint64_t pageSize)
{
    mapPage(vpn,kernel::mm::PageManager::allocate(),userAccessable,pageSize);
}

void VirtualMemory::unmapPage(uint64_t vpn)
{
    VMemMap vmm=resolveMap(vpn);
    kernel::mm::PageManager::deallocate(vmm.pt[vmm.ptIndex].physicalPageNum);
    *reinterpret_cast<uint64_t*>(vmm.pt+vmm.ptIndex)=0;
    if(isNullPagingEntry(vmm.pt))
    {
        kernel::mm::PageManager::deallocate(vmm.pdt[vmm.pdtIndex].physicalPageNum);
        *reinterpret_cast<uint64_t*>(vmm.pdt+vmm.pdtIndex)=0;
        if(isNullPagingEntry(vmm.pdt))
        {
            kernel::mm::PageManager::deallocate(vmm.pdpt[vmm.pdptIndex].physicalPageNum);
            *reinterpret_cast<uint64_t*>(vmm.pdpt+vmm.pdptIndex)=0;
            if(isNullPagingEntry(vmm.pdpt))
            {
                kernel::mm::PageManager::deallocate(vmm.pml4[vmm.pml4Index].physicalPageNum);
                *reinterpret_cast<uint64_t*>(vmm.pml4+vmm.pml4Index)=0;
            }
        }
    }
}

VMemMap VirtualMemory::resolveMap(uint64_t pml4PPN,uint64_t vpn)
{
    VMemMap vmm;

    vmm.ptIndex=vpn;
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

void VirtualMemory::mapKernelPage(uint64_t vpn,uint64_t ppn)
{
    VMemMap vmm=resolveMap(reinterpret_cast<uint64_t>(KernelPageFrame::pml4)/__PAGE_SIZE,vpn);
    vmm.pt[vmm.ptIndex].physicalPageNum=ppn;
    vmm.pt[vmm.ptIndex].writable=1;
    vmm.pt[vmm.ptIndex].present=1;
    refreshPaging();
}

void VirtualMemory::unmapKernelPage(uint64_t vpn)
{
    VMemMap vmm=resolveMap(reinterpret_cast<uint64_t>(KernelPageFrame::pml4)/__PAGE_SIZE,vpn);
    *reinterpret_cast<uint64_t*>(vmm.pt+vmm.ptIndex)=0;
    refreshPaging();
}

template<class T>
void VirtualMemory::setPagingEntry(T* entries,size_t index,size_t ppn,
        uint64_t isToClear,uint64_t userAccessable,uint64_t writable)
{
    if(isToClear)
        std::memset((void*)getAddressFromPPN(ppn),0,__PAGE_SIZE);
    entries[index].physicalPageNum=ppn;
    entries[index].userAccessable=userAccessable;
    entries[index].writable=writable;
    entries[index].present=1;
}

template<class T,class traits>
bool VirtualMemory::isNullPagingEntry(T* entries)
{
    for(size_t i=0;i<traits::size;++i)
    {
        if(entries[i].present)
            return false;
    }
    return true;
}

}   // end of namespace arch::x86::x64
