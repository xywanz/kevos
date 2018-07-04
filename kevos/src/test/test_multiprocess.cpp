
#include <arch/common/assert.h>

#include <arch/x86/x64/multitask_detail.h>
#include <kernel/mm/page_alloc.h>

#include <cstdlib>

using namespace multitask;

void test_process_1()
{
    while(1)
        *((uint16_t*)(0xB8000+2))=((std::rand()%128)<<8)+'e';
}

void test_process_2()
{
    while(1)
        *((uint16_t*)(0xB8000+4))=((std::rand()%128)<<8)+'v';
}

void test_process_3()
{
    while(1)
        *((uint16_t*)(0xB8000+6))=((std::rand()%128)<<8)+'o';
}

void test_process_4()
{
    while(1)
        *((uint16_t*)(0xB8000+8))=((std::rand()%128)<<8)+'s';
}

void test_process_5()
{
    while(1){}
}

void test_multiprocess_main()
{
    ProcessHelper::createKernelProcess((void*)test_process_1);
    ProcessHelper::createKernelProcess((void*)test_process_1);
    ProcessHelper::createKernelProcess((void*)test_process_2);
    ProcessHelper::createKernelProcess((void*)test_process_3);
    ProcessHelper::createKernelProcess((void*)test_process_4);
    ProcessHelper::createKernelProcess((void*)test_process_4);
    ProcessHelper::createKernelProcess((void*)test_process_4);
    // ProcessHelper::createUserProcess((void*)test_process_5);

    // std::size_t codeStart=0x100000000;
    // std::size_t stackStart=0xFFF00000000;
    // using namespace mm::vm;
    // using namespace mm::page;
    // auto stackPPN=PageAllocator::allocate();
    // auto codePPN=PageAllocator::allocate();
    // auto stack=reinterpret_cast<void*>(VirtualMemory::getAddressFromPPN(stackPPN));
    // auto code=reinterpret_cast<void*>(VirtualMemory::getAddressFromPPN(codePPN));
    // std::memcpy(code,(void*)test_process_5,4096);
    // VirtualMemory* vm=new VirtualMemory;
    // vm->mapKernelSpace();
    // vm->mapPage(codeStart/pageSize,codePPN,1);
    // vm->mapPage(stackStart/pageSize,stackPPN,1);
    // vm->loadPML4();
    // using f=void (*)();
    // ((f)codeStart)();
}