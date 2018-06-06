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

#ifndef _STL_FOR_EACH_N_HPP_
#define _STL_FOR_EACH_N_HPP_

namespace std
{

template<class ExecutionPolicy,class ForwardIterator,class Size,class UnaryFunction>
constexpr ForwardIterator for_each_n(ExecutionPolicy&& policy,ForwardIterator first,Size n,UnaryFunction f);

template<class InputIterator,class Size,class UnaryFunction>
constexpr InputIterator for_each_n(InputIterator first,Size n,UnaryFunction f)
{
    for(;n>0;--n,++first)
        f(*first);
    return first;
}

}

#endif

