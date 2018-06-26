
#include <arch/common/assert.h>

#include <arch/x86/x64/vm.h>
#include <arch/x86/x64/kpaging.h>

using namespace mm::vm;
using namespace mm::page;

void test_resolve_map_main()
{
    auto vmm=VirtualMemory::resolveMap(((uint64_t)kernel::pml4)/pageSize,0);
    assert(vmm.pdpt==kernel::pdpt);
    assert(vmm.pdt==kernel::pdt);
    assert(vmm.pt==kernel::pt);
    assert(vmm.pml4Index==0);
    assert(vmm.pdptIndex==0);
    assert(vmm.pdtIndex==0);
    assert(vmm.ptIndex==0);

    vmm=VirtualMemory::resolveMap(((uint64_t)kernel::pml4)/pageSize,512);
    assert(vmm.pdpt==kernel::pdpt);
    assert(vmm.pdt==kernel::pdt);
    assert(vmm.pt==kernel::pt+512);
    assert(vmm.pml4Index==0);
    assert(vmm.pdptIndex==0);
    assert(vmm.pdtIndex==1);
    assert(vmm.ptIndex==0);
}
