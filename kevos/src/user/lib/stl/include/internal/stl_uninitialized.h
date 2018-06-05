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

#include <internal/stl_construct.h>

#include <iterator>
#include <algorithm>

#include <cstring>

namespace std
{

template<class RandomAccessIterator,class OutputIterator,class Distance>
inline OutputIterator __uninitialized_copy_d(RandomAccessIterator first,RandomAccessIterator last,
                        OutputIterator result,Distance*)
{
    for(Distance d=last-first;d>0;--d,++first,++result)
        construct(&*result,*first);
    return result;
}

template<class RandomAccessIterator,class OutputIterator>
inline OutputIterator __uninitialized_copy_dispatch(RandomAccessIterator first,RandomAccessIterator last,
                        OutputIterator result,random_access_iterator_tag)
{
    return __uninitialized_copy_d(first,last,result,difference_type(first));
}

template<class InputIterator,class OutputIterator>
inline OutputIterator __uninitialized_copy_dispatch(InputIterator first,InputIterator last,
                        OutputIterator result,input_iterator_tag)
{
    for(;first!=last;++first,++result)
    {
        construct(&*result,first);
    }
    return result;
}

template <class InputIterator,class OutputIterator>
inline OutputIterator uninitialized_copy(InputIterator first,InputIterator last,OutputIterator result)
{
    return __uninitialized_copy_dispatch(first,last,result,category(first));
}

inline char* uninitialized_copy(const char* first,const char* last,char* result)
{
    memmove(result,first,last-first);
    return result+(last-first);
}

inline wchar_t* uninitialized_copy(const wchar_t* first,const wchar_t* last,wchar_t* result)
{
    memmove(result,first,reinterpret_cast<size_t>(last)-reinterpret_cast<size_t>(first));
    return result+(last-first);
}


template <class InputIterator,class T>
inline void uninitialized_fill(InputIterator first,InputIterator last,const T& x)
{
    for(;first<last;++first)
    {
        construct(&*first,x);
    }
}

template <class InputIterator,class T>
inline void uninitialized_fill_n(InputIterator first,size_t n,const T& x)
{
    while(n--)
    {
        construct(&*(first++),x);
    }
}


}

#endif
