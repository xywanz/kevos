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

#include <string.h>

void* memmove(void* dst,const void* src,size_t count)
{
    void* ret=dst;
    if(dst<src)
    {
        while(count--)
        {
            *(char*)dst=*(char*)src;
            dst=(char*)dst+1;
            src=(char*)src+1;
        }
    }
    else
    {
        dst=(char*)dst+count;
        src=(char*)src+count;
        while(count--)
        {
            *(char*)dst=*(char*)src;
            dst=(char*)dst-1;
            src=(char*)src-1;
        }
    }
    return ret;
}
