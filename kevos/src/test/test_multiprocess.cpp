
#include <arch/common/assert.h>

#include <arch/x86/x64/process.h>

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
    char* stack1=new char[0x150];
    char* stack2=new char[0x150];
    char* stack3=new char[0x150];
    char* stack4=new char[0x150];
    ProcessManager::createKernelProcess((void*)test_process_1,stack1+0x150);
    ProcessManager::createKernelProcess((void*)test_process_2,stack2+0x150);
    ProcessManager::createKernelProcess((void*)test_process_3,stack3+0x150);
    ProcessManager::createKernelProcess((void*)test_process_4,stack4+0x150);
}