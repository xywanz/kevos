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

#ifndef _STL_COPY_HPP_
#define _STL_COPY_HPP_

#include <cstring>
#include <iterator>

namespace std
{

template<class T>
inline T* __copy_t(const T* first,const T* last,T* result)
{
    memmove(result,first,reinterpret_cast<size_t>(last)-reinterpret_cast<size_t>(first));
    return result+(last-first);
}

template<class RandomAccessIterator,class OutputIterator,class Distance>
inline OutputIterator __copy_d(RandomAccessIterator first,RandomAccessIterator last,
                OutputIterator result,Distance*)
{
    for(Distance d=last-first;d>0;--d,++first,++result)
    {
        *result=*first;
    }
    return result;
}

template<class RandomAccessIterator,class OutputIterator>
inline OutputIterator __copy(RandomAccessIterator first,RandomAccessIterator last,
                OutputIterator result,random_access_iterator_tag)
{
    return __copy_d(first,last,result,difference_type(first));
}

template<class InputIterator,class OutputIterator>
inline OutputIterator __copy(InputIterator first,InputIterator last,
                OutputIterator result,input_iterator_tag)
{
    for(;first!=last;++first,++result)
    {
        *result=*first;
    }
    return result;
}

template <class InputIterator,class OutputIterator,class IteratorCategory>
inline OutputIterator __copy_dispatch(InputIterator first,InputIterator last,OutputIterator result,
                            IteratorCategory input_iter_tag)
{
    return __copy(first,last,result,input_iter_tag);
}

template<class T,class IteratorCategory>
inline T* __copy_dispatch(const T* first,const T* last,T* result,random_access_iterator_tag)
{
    return __copy_t(first,last,result);
}

template<class T,class IteratorCategory>
inline T* __copy_dispatch(T* first,T* last,T* result,random_access_iterator_tag)
{
    return __copy_t((const T*)first,(const T*)last,result);
}

template <class InputIterator,class OutputIterator>
inline OutputIterator copy(InputIterator first,InputIterator last,OutputIterator result)
{
    return __copy_dispatch(first,last,result,category(first));
}

inline char* copy(const char* first,const char* last,char* result)
{
    memmove(result,first,last-first);
    return result+(last-first);
}

inline wchar_t* copy(const wchar_t* first,const wchar_t* last,wchar_t* result)
{
    memmove(result,first,reinterpret_cast<size_t>(last)-reinterpret_cast<size_t>(first));
    return result+(last-first);
}

}

#endif
