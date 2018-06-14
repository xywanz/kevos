
#include <arch/common/assert.h>

#include <arch/x86/x64/multitask_detail.h>

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

void test_multiprocess_main()
{
    ProcessManager::createKernelProcess((void*)test_process_1);
    ProcessManager::createKernelProcess((void*)test_process_1);
    ProcessManager::createKernelProcess((void*)test_process_2);
    ProcessManager::createKernelProcess((void*)test_process_3);
    ProcessManager::createKernelProcess((void*)test_process_4);
    ProcessManager::createKernelProcess((void*)test_process_4);
    ProcessManager::createUserProcess((void*)test_process_4);
}