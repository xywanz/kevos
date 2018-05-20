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

#include <stdlib.h>


char* itoa(int value,char* string,int radix)
{
    char *ret=string;
    if(radix==16)
    {
        *string++='0';
        *string++='x';
    }
    else if(radix==8)
    {
        *string++='0';
    }
    if(value<0)
        *string++='-';
    int tmp,i=0;
    char c;
    do
    {
        tmp=value%radix;
        string[i++]=tmp<10?tmp+'0':tmp+'a'-10;
    }while(value/=radix);
    string[i--]=0;
    for(int j=0;j<i;++j,--i)
    {
        c=string[j];
        string[j]=string[i];
        string[i]=c;
    }
    return ret;
}