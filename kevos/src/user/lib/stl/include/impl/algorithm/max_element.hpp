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

#ifndef _STL_MAX_ELEMENT_HPP_
#define _STL_MAX_ELEMENT_HPP_

namespace std
{

/**
 *@brief since c++17
 */
template <class ForwardIterator>
constexpr ForwardIterator max_element(ForwardIterator first,ForwardIterator last)
{
    auto _max=first;
    ++first;
    for(;first!=last;++first)
    {
        if(*first>*_max)
            _max=first;
    }
    return _max;
}

/**
 *@brief since c++17
 */
template <class ForwardIterator,class Compare>
constexpr ForwardIterator max_element(ForwardIterator first,ForwardIterator last,Compare comp)
{
    auto _max=first;
    ++first;
    for(;first!=last;++first)
    {
        if(comp(*_max,*first))
            _max=first;
    }
    return _max;
}

/**
 *@brief since c++17
 */
template <class ExecutionPolicy,class ForwardIterator,class Compare>
ForwardIterator max_element(ExecutionPolicy&& policy,ForwardIterator first,ForwardIterator last,Compare comp);
    
}

#endif
