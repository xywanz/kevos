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

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace std
{

int vsprintf(char* str,const char* fmt,va_list args)
{
    static char buf[16]={0};
    char *ptr=str,*p;
    while(*fmt)
    {
        if(*fmt=='%')
        {
            switch(*(++fmt))
            {
                case 'd':
                case 'i':
                    p=itoa(va_arg(args,int),buf,10);
                    while(*p)
                        *str++=*p++;
                    break;
                case 'u':
                    p=itoa(va_arg(args,unsigned int),buf,10);
                    while(*p)
                        *str++=*p++;
                    break;
                case 's':
                    p=va_arg(args,char*);
                    while(*p)
                        *str++=*p++;
                    break;
                case 'o':
                    p=itoa(va_arg(args,int),buf,8);
                    while(*p)
                        *str++=*p++;
                    break;
                case 'p':
                    p=itoa(va_arg(args,unsigned int),buf,16);
                    while(*p)
                        *str++=*p++;
                    break;
                case 'c':
                    *str++=va_arg(args,int);
                    break;
                case '%':
                    *str++='%';
                    break;
                default:
                    break;
            }
            ++fmt;
        }
        *str++=*fmt++;
    }
    *str=0;
    return strlen(ptr);
}

}
