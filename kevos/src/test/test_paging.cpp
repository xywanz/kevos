
#include <arch/common/assert.h>

#include <arch/x86/x64/vm.h>
#include <kernel/mm/page_alloc.h>
#include <kernel/mm/mem_layout.h>

using namespace mm::vm;
using namespace mm::page;

void test_paging_main()
{
    VirtualMemory* vm=new VirtualMemory;
    // for(std::size_t i=0;i<kernel_end_ppn;++i)
    // {
    //     vm->mapPage(i,i,1);
    // }
    vm->mapKernelSpace();
    vm->mapPage(0x100000000/pageSize,PageAllocator::allocate(),1);
    vm->mapPage(0xFFF00000000/pageSize,PageAllocator::allocate(),1);
    vm->loadPML4();
    vm->resolveMap(0xFFF00000000);
    // VirtualMemory::loadKernelPML4();
    // auto vmm=vm->resolveMap(0xFFFFF000/pageSize);
    // assert(vmm.pml4!=0);
    // assert(vmm.pdptPPN!=0);
    // assert(vmm.pdtPPN!=0);
    // assert(vmm.ptPPN!=0);
    // assert(vmm.pml4!=nullptr);
    // assert(vmm.pdpt!=nullptr);
    // assert(vmm.pdt!=nullptr);
    // assert(vmm.pt!=nullptr);
    *((char*)0x100000000)=1;
    *((char*)0x100000001)=1;
    *((char*)0xFFF00000000)=1;
    // *((char*)0x100000000)=1;
    VirtualMemory::loadKernelPML4();
    delete vm;
}