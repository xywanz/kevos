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

#include <arch/common/assert.h>

#include <cstdlib>

std::size_t print(std::size_t pos,const char* buf)
{
    auto addr=(unsigned char*)(0xB8000+pos*2);
    std::size_t i;
    for(i=0;buf[i]!=0;++i)
    {
        addr[2*i]=buf[i];
        addr[2*i+1]=0x75;
    }
    return i;
}

void __assert(const char* cond,uint32_t line,const char* file)
{
    static std::size_t pos=0;
    static char buffer[16];
    std::size_t i=print(pos,cond);
    std::size_t j=print(pos+i+2,file);
    std::itoa(line,buffer,10);
    print(pos+i+j+4,buffer);
    pos+=160;
}
