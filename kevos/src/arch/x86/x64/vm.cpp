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
#include <kernel/mm/page_alloc.h>

#include <cstring>

namespace mm::vm
{

using namespace page;

VirtualMemory::VirtualMemory()
{
    m_pml4PPN=PageAllocator::allocate();
    bzero(m_pml4PPN);
}

VirtualMemory::~VirtualMemory()
{
    PML4E* pml4=reinterpret_cast<PML4E*>(getAddressFromPPN(m_pml4PPN));
    for(std::size_t pml4i=0;pml4i<pml4EntryNum;++pml4i)
    {
        if(pml4[pml4i].present)
        {
            PDPTE* pdpt=reinterpret_cast<PDPTE*>(getAddressFromPPN(pml4[pml4i].physicalPageNum));
            for(std::size_t pdpti=0;pdpti<pdptEntryNum;++pdpti)
            {
                if(pdpt[pdpti].present)
                {
                    PDTE* pdt=reinterpret_cast<PDTE*>(getAddressFromPPN(pdpt[pdpti].physicalPageNum));
                    for(std::size_t pdti=0;pdti<pdtEntryNum;++pdti)
                    {
                        if(pdt[pdti].present)
                        {
                            PTE* pt=reinterpret_cast<PTE*>(getAddressFromPPN(pdt[pdti].physicalPageNum));
                            for(std::size_t pti=0;pti<ptEntryNum;++pti)
                            {
                                if(pt[pti].present)
                                {
                                    PageAllocator::deallocate(pt[pti].physicalPageNum);
                                }
                            }
                            PageAllocator::deallocate(pdt[pdti].physicalPageNum);
                        }
                    }
                    PageAllocator::deallocate(pdpt[pdpti].physicalPageNum);
                }
            }
            PageAllocator::deallocate(pml4[pml4i].physicalPageNum);
        }
    }
    PageAllocator::deallocate(m_pml4PPN);
}

void VirtualMemory::mapPage(uint64_t vpn,uint64_t ppn,uint64_t userAccessable,uint64_t pageSize)
{
    VMemMap vmm=resolveMap(vpn);
    if(!vmm.pml4[vmm.pml4Index].present)
    {
        vmm.pdptPPN=PageAllocator::allocate(pageSize);
        setPagingEntry(vmm.pml4,vmm.pml4Index,vmm.pdptPPN,true,userAccessable,1);
        vmm.pdpt=reinterpret_cast<PDPTE*>(getAddressFromPPN(vmm.pdptPPN));
    }
    if(!vmm.pdpt[vmm.pdptIndex].present)
    {
        vmm.pdtPPN=PageAllocator::allocate(pageSize);
        setPagingEntry(vmm.pdpt,vmm.pdptIndex,vmm.pdtPPN,true,userAccessable,1);
        vmm.pdt=reinterpret_cast<PDTE*>(getAddressFromPPN(vmm.pdtPPN));
    }
    if(!vmm.pdt[vmm.pdtIndex].present)
    {
        vmm.ptPPN=PageAllocator::allocate(pageSize);
        setPagingEntry(vmm.pdt,vmm.pdtIndex,vmm.ptPPN,true,userAccessable,1);
        vmm.pt=reinterpret_cast<PTE*>(getAddressFromPPN(vmm.ptPPN));
    }
    setPagingEntry(vmm.pt,vmm.ptIndex,ppn,false,userAccessable,1);
}

void VirtualMemory::fillPageFrame(uint64_t vpn,uint64_t userAccessable,uint64_t pageSize)
{
    // mapPage(vpn,PageAllocator::allocate(),userAccessable,pageSize);
}

void VirtualMemory::unmapPage(uint64_t vpn)
{
    VMemMap vmm=resolveMap(vpn);
    PageAllocator::deallocate(vmm.pt[vmm.ptIndex].physicalPageNum);
    *reinterpret_cast<uint64_t*>(vmm.pt+vmm.ptIndex)=0;
    if(isNullPagingEntry(vmm.pt))
    {
        PageAllocator::deallocate(vmm.pdt[vmm.pdtIndex].physicalPageNum);
        *reinterpret_cast<uint64_t*>(vmm.pdt+vmm.pdtIndex)=0;
        if(isNullPagingEntry(vmm.pdt))
        {
            PageAllocator::deallocate(vmm.pdpt[vmm.pdptIndex].physicalPageNum);
            *reinterpret_cast<uint64_t*>(vmm.pdpt+vmm.pdptIndex)=0;
            if(isNullPagingEntry(vmm.pdpt))
            {
                PageAllocator::deallocate(vmm.pml4[vmm.pml4Index].physicalPageNum);
                *reinterpret_cast<uint64_t*>(vmm.pml4+vmm.pml4Index)=0;
            }
        }
    }
}

VMemMap VirtualMemory::resolveMap(uint64_t pml4PPN,uint64_t vpn)
{
    VMemMap vmm;

    vmm.ptIndex=vpn;
    vmm.pdtIndex=vmm.ptIndex/ptEntryNum;
    vmm.pdptIndex=vmm.pdtIndex/pdtEntryNum;
    vmm.pml4Index=vmm.pdptIndex/pdptEntryNum;

    vmm.ptIndex%=ptEntryNum;
    vmm.pdtIndex%=pdtEntryNum;
    vmm.pdptIndex%=pdptEntryNum;
    vmm.pml4Index%=pml4EntryNum;

    vmm.pml4PPN=pml4PPN;
    vmm.pml4=reinterpret_cast<PML4E*>(getAddressFromPPN(pml4PPN));

    vmm.pdptPPN=vmm.pdtPPN=vmm.ptPPN=0;
    vmm.pdpt=nullptr;
    vmm.pdt=nullptr;
    vmm.pt=nullptr;
    
    vmm.pageSize=pageSize;

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
    VMemMap vmm=resolveMap(reinterpret_cast<uint64_t>(kernel::pml4)/pageSize,vpn);
    vmm.pt[vmm.ptIndex].physicalPageNum=ppn;
    vmm.pt[vmm.ptIndex].writable=1;
    vmm.pt[vmm.ptIndex].present=1;
    refreshPaging();
}

void VirtualMemory::unmapKernelPage(uint64_t vpn)
{
    VMemMap vmm=resolveMap(reinterpret_cast<uint64_t>(kernel::pml4)/pageSize,vpn);
    *reinterpret_cast<uint64_t*>(vmm.pt+vmm.ptIndex)=0;
    refreshPaging();
}

void VirtualMemory::bzero(uint64_t ppn)
{
    std::memset((void*)getAddressFromPPN(ppn),0,pageSize);
}

template<class T>
void VirtualMemory::setPagingEntry(T* entries,std::size_t index,std::size_t ppn,
        bool isToClear,uint64_t userAccessable,uint64_t writable)
{
    if(isToClear)
        std::memset((void*)getAddressFromPPN(ppn),0,pageSize);
    entries[index].physicalPageNum=ppn;
    entries[index].userAccessable=userAccessable;
    entries[index].writable=writable;
    entries[index].present=1;
}

template<class T,class traits>
bool VirtualMemory::isNullPagingEntry(T* entries)
{
    for(std::size_t i=0;i<traits::size;++i)
    {
        if(entries[i].present)
            return false;
    }
    return true;
}

}
