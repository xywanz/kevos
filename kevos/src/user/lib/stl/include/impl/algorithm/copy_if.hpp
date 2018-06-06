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

#ifndef _STL_COPY_IF_HPP_
#define _STL_COPY_IF_HPP_

#include <iterator>

namespace std
{

template<class RandomAccessIterator,class OutputIterator,class UnaryPredicate,class Distance>
inline OutputIterator __copy_if_d(RandomAccessIterator first,RandomAccessIterator last,
                        OutputIterator result,UnaryPredicate p,Distance*)
{
    for(Distance d=last-first;d>0;++first)
    {
        if(p(first))
            *result++=*first;
    }
    return result;
}

template<class InputIterator,class OutputIterator,class UnaryPredicate>
inline OutputIterator __copy_if(InputIterator first,InputIterator last,
                        OutputIterator result,UnaryPredicate p,input_iterator_tag)
{
    for(;first!=last;++first)
    {
        if(p(first))
            *result++=*first;
    }
    return result;
}

template<class RandomAccessIterator,class OutputIterator,class UnaryPredicate>
inline OutputIterator __copy_if(RandomAccessIterator first,RandomAccessIterator last,
                        OutputIterator result,UnaryPredicate p,random_access_iterator_tag)
{
    return __copy_if_d(first,last,result,p,difference_type(first));
}

template<class InputIterator,class OutputIterator,class UnaryPredicate>
inline OutputIterator copy_if(InputIterator first,InputIterator last,OutputIterator result,UnaryPredicate p)
{
    return __copy_if(first,last,result,p,category(first));
}

}

#endif
