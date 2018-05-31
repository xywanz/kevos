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

#ifndef _STL_STL_CONSTRUCT_
#define _STL_STL_CONSTRUCT_

#include <type_traits.h>

#include <new>

namespace std
{

template <class T1,class T2>
inline void construct(T1* p,const T2& x)
{
    p=new(p) T1(x);
}

template <class T>
inline void destroy(T* p)
{
    p->~T();
}

template <class ForwardIterator>
inline void __destroy(ForwardIterator first,ForwardIterator last,true_type)
{
    for(;first<last;++first)
        destroy(&*first);
}

template <class ForwardIterator>
inline void __destroy(ForwardIterator first,ForwardIterator last,false_type)
{
}

template <class ForwardIterator>
inline void destroy(ForwardIterator first,ForwardIterator last)
{
    __destroy(first,last,type_traits<typename ForwardIterator::value_type>::has_trival_destuctor());
}

inline void destroy(char*,char*){}
inline void destroy(wchar_t*,wchar_t*){}

}


#endif
