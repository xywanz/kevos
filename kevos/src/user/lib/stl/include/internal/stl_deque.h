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

#include <internal/stl_alloc.h>
#include <internal/stl_uninitialized.h>

#include <algorithm>

#include <cstddef>


namespace std
{

inline constexpr size_t __deque_buffer_size(size_t n,size_t sz)
{
    return n?n:(sz<512?(512/sz):1);
}

template <class T,class Pointer,class Reference,size_t BufferSize>
class __deque_iterator;

template <class T,class Pointer,class Reference,size_t BufferSize>
class __deque_reverse_iterator;



template <class T,class Alloc=alloc,size_t BufferSize=0>
class deque
{
public:
    using value_type=T;
    using pointer=T*;
    using reference= T&;
    using size_type=size_t;
    using difference_type=ptrdiff_t;
    using iterator=__deque_iterator<T,T*,T&,BufferSize>;
    using const_iterator=__deque_iterator<T,const T*,const T&,BufferSize>;
    using reverse_iterator=__deque_reverse_iterator<T,T*,T&,BufferSize>;
    using const_reverse_iterator=__deque_reverse_iterator<T,const T*,const T&,BufferSize>;

protected:
    using data_allocator=simple_alloc<T,Alloc>;
    using map_allocator=simple_alloc<pointer,Alloc>;

    using map_pointer=pointer*;

    void fill_initialize(size_type n,const value_type& x);

    void create_map_and_nodes(size_type n);

    static size_type buffer_size()
    {
        return __deque_buffer_size(BufferSize,sizeof(T));
    }

public:

    deque(size_type n,const value_type& x)
    {
        fill_initialize(n,x);
    }

    data_allocator get_allocator()const
    {
        return data_allocator();
    }

    iterator begin()const
    {
        return _begin;
    }

    iterator end()const
    {
        return _end;
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(_end-1);
    }

    reverse_iterator rend()
    {
        return reverse_iterator(_begin-1);
    }

    reference operator[](size_type n)
    {
        return _begin[n];
    }

    reference front()
    {
        return *_begin;
    }

    const reference front()const
    {
        return *_begin;
    }

    reference back()
    {
        return *(_end-1);
    }

    const reference back()const
    {
        return *(_end-1);
    }

    size_type size()const
    {
        return _end-_begin;
    }

    size_type max_size()const
    {
        size_type(-1)/sizeof(T);
    }

    bool empty()const
    {
        return _begin==_end;
    }

protected:
    iterator _begin;
    iterator _end;
    map_pointer map;
    size_type map_size;
};

template <class T,class Alloc,size_t BufferSize>
void deque<T,Alloc,BufferSize>::fill_initialize(typename deque<T,Alloc,BufferSize>::size_type n,const T& x)
{

}

template <class T,class Alloc,size_t BufferSize>
void deque<T,Alloc,BufferSize>::create_map_and_nodes(typename deque<T,Alloc,BufferSize>::size_type n)
{
    size_type num_nodes=n/buffer_size()+1;
    map_size=max(num_nodes+2,size_type(8));
    map=map_allocator::allocate(map_size);

}





template <class T,class Pointer,class Reference,size_t BufferSize>
class __deque_iterator
{
public:
    using iterator_category=random_access_iterator_tag;
    using value_type=T;
    using pointer=Pointer;
    using reference=Reference;
    using size_type=size_t;
    using difference_type=ptrdiff_t;
    using iterator=__deque_iterator<T,Pointer,Reference,BufferSize>;
    using const_iterator=__deque_iterator<T,const T*,const T&,BufferSize>;

    using self=__deque_iterator;

protected:

    using map_pointer=pointer*;

    static size_t buffer_size()
    {
        return __deque_buffer_size(BufferSize,sizeof(T));
    }

    void set_node(map_pointer new_node)
    {
        node=new_node;
        first=*node;
        last=first+buffer_size();
    }

public:
    reference operator*()
    {
        return *current;
    }

    pointer operator->()
    {
        return current;
    }

    difference_type operator-(const self& x)
    {
        return (node-x.node-1)*difference_type(buffer_size())+(current-first)+(x.last-x.current);
    }

    self& operator--()
    {
        if(current==first)
        {
            set_node(node-1);
            current=last;
        }
        --current;
        return *this;
    }

    self operator--(int)
    {
        self ret=*this;
        --*this;
        return ret;
    }

    self& operator++()
    {
        ++current;
        if(current==last)
        {
            set_node(node+1);
            current=first;
        }
        return *this;
    }

    self operator++(int)
    {
        self ret=*this;
        ++*this;
        return ret;
    }

    self& operator+=(difference_type n)
    {
        difference_type offset=n+(current-first);
        if(offset>=0 && offset<buffer_size())
        {
            current+=n;
        }
        else
        {
            difference_type node_offset=offset>0?
                offset/buffer_size():
                -((-offset-1)/difference_type(buffer_size()))-1;
            set_node(node+node_offset);
            current=first+(offset-node_offset*difference_type(buffer_size()));
        }
        return *this;
    }

    self& operator-=(difference_type n)
    {
        return *this+=-n;
    }

    self operator+(difference_type n)const
    {
        self ret=*this;
        return ret+=n;
    }

    self operator-(difference_type n)const
    {
        self ret=*this;
        return ret-=n;
    }

    reference operator[](difference_type n)const
    {
        return *(*this+n);
    }

    bool operator==(const self& x)const
    {
        return node==x.node&&current==x.current;
    }

    bool operator!=(const self& x)const
    {
        return x!=*this;
    }

    bool operator<(const self& x)const
    {
        return (node==x.node)?(current<x.current):(node<x.node);
    }

    bool operator<=(const self& x)const
    {
        return (node==x.node)?(current<=x.current):(node<=x.node);
    }

    bool operator>(const self& x)const
    {
        return !(*this<=x);
    }

    bool operator>=(const self& x)const
    {
        return !(*this<x);
    }

protected:
    pointer current;
    pointer first;
    pointer last;
    map_pointer node;
};


template <class T,class Pointer,class Reference,size_t BufferSize>
class __deque_reverse_iterator
{
public:
    using iterator_category=random_access_iterator_tag;
    using value_type=T;
    using pointer=Pointer;
    using reference=Reference;
    using size_type=size_t;
    using difference_type=ptrdiff_t;
    using iterator=__deque_reverse_iterator<T,Pointer,Reference,BufferSize>;
    using const_iterator=__deque_reverse_iterator<T,const T*,const T&,BufferSize>;

    using self=__deque_reverse_iterator;

protected:
    using forward_iterator=__deque_iterator<T,T*,T&,BufferSize>;
    using const_forward_iterator=__deque_iterator<T,const T*,const T&,BufferSize>;

public:

    __deque_reverse_iterator(const iterator& x):iter(x)
    {
    }

    reference operator*()
    {
        return *iter;
    }

    pointer operator->()
    {
        return &(*iter);
    }

    difference_type operator-(const self& x)
    {
        return x.iter-iter;
    }

    self& operator--()
    {
        ++iter;
        return *this;
    }

    self operator--(int)
    {
        self ret=*this;
        --*this;
        return ret;
    }

    self& operator++()
    {
        --iter;
        return *this;
    }

    self operator++(int)
    {
        self ret=*this;
        ++*this;
        return ret;
    }

    self& operator+=(difference_type n)
    {
        iter-=n;
        return *this;
    }

    self& operator-=(difference_type n)
    {
        return *this+=n;
    }

    self operator+(difference_type n)const
    {
        self ret=*this;
        return ret-=n;
    }

    self operator-(difference_type n)const
    {
        self ret=*this;
        return ret+=n;
    }

    reference operator[](difference_type n)const
    {
        return *(*this-n);
    }

    bool operator==(const self& x)const
    {
        return iter==x.iter;
    }

    bool operator!=(const self& x)const
    {
        return x!=*this;
    }

    bool operator<(const self& x)const
    {
        return iter>x.iter;
    }

    bool operator<=(const self& x)const
    {
        return iter>=x.iter;
    }

    bool operator>(const self& x)const
    {
        return !(*this<=x);
    }

    bool operator>=(const self& x)const
    {
        return !(*this<x);
    }

protected:
    forward_iterator iter;
};

}

#endif
