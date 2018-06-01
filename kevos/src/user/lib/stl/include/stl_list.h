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

#ifndef _STL_STL_LIST_H_
#define _STL_STL_LIST_H_

#include <stl_alloc.h>
#include <stl_iterator.h>

namespace std
{

template <class T>
class __list_node
{
public:
    __list_node* next;
    __list_node* prev;
    T data;
};

template <class T,class Pointer,class Reference>
class __list_iterator
{
public:
    using iterator_category=bidirection_iterator_tag;
    using value_type=T;
    using pointer=Pointer;
    using reference=Reference;
    using size_type=size_t;
    using difference_type=ptrdiff_t;

    using iterator=__list_iterator<T,T*,T&>;
    using self=__list_iterator<T,Pointer,Reference>;
    using link_type=__list_node<T>*;

    __list_iterator()
    {
    }

    __list_iterator(link_type x):node(x)
    {
    }

    __list_iterator(const __list_iterator& other):node(other.node)
    {
    }

    bool operator==(const self& other)const
    {
        return other.node==node;
    }

    bool operator!=(const self& other)const
    {
        return other.node!=node;
    }

    reference operator*()const
    {
        return node->data;
    }

    pointer operator->()const
    {
        return &(operator*());
    }

    self& operator++()
    {
        node=node->next;
        return *this;
    }

    self operator++(int)
    {
        self ret=*this;
        node=node->next;
        return ret;
    }

    self& operator--()
    {
        node=node->prev;
        return *this;
    }

    self operator--(int)
    {
        self ret=*this;
        node=node->next;
        return ret;
    }

protected:
    link_type node;    
};

template <class T,class Alloc=alloc>
class list
{
protected:
    using list_node=__list_node<T>;
    using link_type=list_node*;
    
    using list_node_allocator=simple_alloc<list_node,Alloc>;

    link_type alloc_node()
    {
        return list_node_allocator::allocate();
    }

    void dealloc_node(link_type p)
    {
        list_node_allocator::deallocate(p);
    }

    link_type create_node(const T& x)
    {
        link_type p=alloc_node();
        construct(&(p->data),x);
        return p;
    }

    void destroy_node(link_type p)
    {
        destroy((&p->data));
        dealloc_node(p);
    }

public:
    using iterator=__list_iterator<T,T*,T&>;

public:
    list()
    {
        node=alloc_node();
        node->next=node;
        node->prev=node;
    }

    iterator begin()const
    {
        return node->next;
    }

    iterator end()const
    {
        return node;
    }

    void push_back(const T& x)
    {
        link_type p=create_node(x);
        p->prev=node->prev;
        node->prev=p;
        node->prev->next=p;
        p->next=node;
    }

    void insert(iterator pos,const T& x)
    {

    }

protected:
    link_type node;

};

}

#endif
