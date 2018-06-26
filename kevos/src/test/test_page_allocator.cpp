
#include <arch/common/assert.h>

#include <kernel/mm/page_alloc.h>

using namespace mm::page;


void test_page_allocator_main()
{
    auto p1=PageAllocator::allocate();
    auto p2=PageAllocator::allocate();
    auto p3=PageAllocator::allocate();
    auto p4=PageAllocator::allocate();
    auto p5=PageAllocator::allocate();
    auto p6=PageAllocator::allocate();
    assert(p2-p1==1);
    assert(p3-p2==1);
    assert(p4-p3==1);
    assert(p5-p4==1);
    assert(p6-p5==1);
    PageAllocator::deallocate(p1);
    PageAllocator::deallocate(p2);
    PageAllocator::deallocate(p3);
    PageAllocator::deallocate(p4);
    PageAllocator::deallocate(p5);
    PageAllocator::deallocate(p6);
}