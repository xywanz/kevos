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

#ifndef _STL_STL_DEQUE_H_
#define _STL_STL_DEQUE_H_

#include <stl_alloc.h>
#include <stl_uninitialized.h>

#include <climits>


namespace std
{

template <class T,class Alloc>
class deque;

template <class T,class Alloc=alloc>
class deque
{
public:
    using value_type=T;
    using pointer=T*;
    using reference= T&;
    using size_type=size_t;
    using difference_type=ptrdiff_t;
protected:
    using data_allocator=simple_alloc<T,Alloc>;
    using map_pointer=pointer*;
public:

protected:
    map_pointer map;
    size_type map_size;
};

}

#endif
