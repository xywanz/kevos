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

#include <cstring>

namespace std
{

size_t strlen(const char * str)
{
    const char * char_ptr;
    const unsigned long * longword_ptr;
    register unsigned long longword, magic_bits;
    for (char_ptr =  str;
        ((unsigned long)char_ptr & (sizeof(unsigned long) - 1)) != 0;
        ++ char_ptr)
    {
        if (*char_ptr == '\0')
            return char_ptr -  str;
    }
    longword_ptr = (unsigned long* )char_ptr;
    magic_bits = 0x7efefeffL;
    while (1)
    {
        longword = *longword_ptr++;
        if ((((longword + magic_bits) ^ ~longword) & ~magic_bits) != 0 )
        {
            const char *cp = (const char*)(longword_ptr - 1 );
            if (cp[0] == 0 )
                return cp - str;
            if (cp[1] == 0 )
                return cp - str + 1;
            if (cp[2] == 0 )
                return cp - str + 2;
            if (cp[3] == 0 )
                return cp - str + 3;
        }
    }
}

}