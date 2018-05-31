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

#ifndef _STL_STL_UNINITIALIZED_H_
#define _STL_STL_UNINITIALIZED_H_

#include <stl_construct.h>

#include <cstring>

namespace std
{

template <class InputIterator,class ForwardIterator>
inline ForwardIterator uninitialized_copy(InputIterator first,InputIterator last,ForwardIterator result)
{
    ForwardIterator i=result;
    for(;first!=last;++first,++i)
    {
        construct(&*i,*first);
    }
    return i;
}

template <class ForwardIterator,class T>
inline void uninitialized_fill(ForwardIterator first,ForwardIterator last,const T& x)
{
    for(;first<last;++first)
    {
        construct(&*first,x);
    }
}

template <class ForwardIterator,class T>
inline void uninitialized_fill_n(ForwardIterator first,size_t n,const T& x)
{
    while(n--)
    {
        construct(&*(first++),x);
    }
}

inline char* uninitialized_copy(const char* first,const char* last,char* result)
{
    memmove(result,first,last-first);
    return result+last-first;
}

inline wchar_t* uninitialized_copy(const wchar_t* first,const wchar_t* last,wchar_t* result)
{
    memmove(result,first,(char*)last-(char*)first);
    return result+last-first;
}

}

#endif
