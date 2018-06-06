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

#ifndef _STL_COPY_BACKWARD_HPP_
#define _STL_COPY_BACKWARD_HPP_

#include <impl/algorithm/copy.hpp>

namespace std
{

template<class T>
inline T* __copy_backward_dispatch(const T* first,const T* last,T* result)
{
    return __copy_t(first,last,result);
}

template<class T>
inline T* __copy_backward_dispatch(T* first,T* last,T* result)
{
    return __copy_t((const T*)first,(const T*)last,result);
}

template<class RandomAccessIterator,class BidirectionIterator2,class Distance>
inline BidirectionIterator2 __copy_backward(RandomAccessIterator first,RandomAccessIterator last,
                                        BidirectionIterator2 result,Distance*)
{
    --last;
    for(Distance d=last-first;d>0;--d,--last,--result)
    {
        *result=*last;
    }
    return last;
}

template<class RandomAccessIterator,class BidirectionIterator2>
inline BidirectionIterator2 __copy_backward(RandomAccessIterator first,RandomAccessIterator last,
                                        BidirectionIterator2 result,random_access_iterator_tag)
{
    return __copy_backward_d(first,last,result,difference_type(first));
}

template<class BidirectionIterator1,class BidirectionIterator2>
inline BidirectionIterator2 __copy_backward(BidirectionIterator1 first,BidirectionIterator1 last,
                                        BidirectionIterator2 result,bidirection_iterator_tag)
{
    for(--last;last!=first;--last,--result)
    {
        *result=*last;
    }
    *result=*last;
    return --result;
}

template<class BidirectionIterator1,class BidirectionIterator2>
inline BidirectionIterator2 __copy_dispatch(BidirectionIterator1 first,BidirectionIterator1 last,
                                            BidirectionIterator2 result)
{
    return __copy_backward(first,last,result,category(first));    
}

template<class BidirectionIterator1,class BidirectionIterator2>
inline BidirectionIterator2 copy_backward(BidirectionIterator1 first,BidirectionIterator1 last,
                                            BidirectionIterator2 result)
{
    return __copy_backward_dispatch(first,last,result);
}

}

#endif
