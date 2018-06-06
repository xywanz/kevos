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

#ifndef _STL_FIND_IF_HPP_
#define _STL_FIND_IF_HPP_

namespace std
{

/**
 *@brief since c++17
 */
template <class ExecutionPolicy,class ForwardIterator,class UnaryPredicate>
ForwardIterator find_if(ExecutionPolicy&& policy,ForwardIterator first,ForwardIterator last,UnaryPredicate p);

/**
 *@brief since c++20
 */
template <class InputIterator, class UnaryPredicate>
constexpr InputIterator find_if(InputIterator first,InputIterator last,UnaryPredicate p)
{
    for(;first!=last;++first)
    {
        if(p(first))
            return first;
    }
    return last;
}

}

#endif
