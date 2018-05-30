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

#ifndef _STL_FIRST_ALLOCATOR_
#define _STL_FIRST_ALLOCATOR_

#include <cstddef>

namespace std
{
    
template<class T>
class first_allocator
{
public:

    using value_type=T;
    using pointer=T*;
    using const_pointer=const T*;
    using reference=T&;
    using const_reference=const T&;
    using size_type=size_t;
    using difference_type=ptrdiff_t;

    template<class U>
    struct rebind
    {
        using other=first_allocator<U>;
    };

    first_allocator();

    first_allocator(const first_allocator&);

    template<class U>
    first_allocator(const first_allocator<U>&);

    ~first_allocator();

    const_pointer address(reference x)const;

    pointer allocate(size_type n,void* p=0);

    void deallocate(pointer p,size_type n);

    size_type max_size()const;

    void construct(pointer p,const_reference x);        // new((const void*)p) T(x)

    void destruct(pointer p);

};

}


#endif
