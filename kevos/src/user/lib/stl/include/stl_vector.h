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

#ifndef _STL_STL_VECTOR_H_
#define _STL_STL_VECTOR_H_

#include <stl_alloc.h>
#include <stl_uninitialized.h>

namespace std
{
    
template <class T,class Alloc=alloc>
class vector
{
public:
    using value_type=T;
    using pointer=T*;
    using reference=T&;
    using size_type=size_t;
    using difference_type=ptrdiff_t;
    using iterator=value_type*;

protected:
    using data_allocator=simple_alloc<T,Alloc>;

    iterator _start;
    iterator _end;
    iterator _end_of_storage;

    iterator allocate_and_fill(size_type n,const T& value)
    {
        iterator ret=data_allocator::allocate(n);
        uninitialized_fill_n(ret,n,value);
        return ret;
    }

    void fill_initialize(size_type n,const T& value)
    {
        _start=allocate_and_fill(n,value);
        _end=_start+n;
        _end_of_storage=_end;
    }

    void deallocate()
    {
        if(_start)
            data_allocator::deallocate(_start);
    }

public:
    iterator begin()const
    {
        return _start;
    }

    iterator end()const
    {
        return _end;
    }

    size_type size()const
    {
        return size_type(end()-begin());
    }

    size_type capacity()const
    {
        return size_type(_end_of_storage-begin());
    }

    bool empty()const
    {
        return begin()==end();
    }

    reference operator[](size_type n)
    {
        return *(begin()+n);
    }

    vector():_start(0),_end(0),_end_of_storage(0)
    {
    }

    template <class NumericType>
    vector(NumericType n,const T& value)
    {
        fill_initialize(n,value);
    }

    explicit vector(size_type n)
    {
        fill_initialize(n,T());
    }

    ~vector()
    {
        destroy(_start,_end);
        deallocate();
    }

    reference front()
    {
        return *begin();
    }

    reference back()
    {
        return *(end()-1);
    }

    void push_back(const T& x)
    {
        if(_end!=_end_of_storage)
        {
            construct(_end,x);
            ++_end;
        }
        else
        {    
        }
    }

    void pop_back()
    {
        --_end;
        destroy(_end);
    }

    

};

}


#endif
