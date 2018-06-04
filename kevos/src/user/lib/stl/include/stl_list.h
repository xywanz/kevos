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

    __list_iterator(const self& other):node(other.node)
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

    link_type node;    
};

template <class T,class Pointer,class Reference>
class __list_reverse_iterator
{
public:
    using iterator_category=bidirection_iterator_tag;
    using value_type=T;
    using pointer=Pointer;
    using reference=Reference;
    using size_type=size_t;
    using difference_type=ptrdiff_t;

    using iterator=__list_reverse_iterator<T,T*,T&>;
    using self=__list_reverse_iterator<T,Pointer,Reference>;
    using link_type=__list_node<T>*;

    __list_reverse_iterator()
    {
    }

    __list_reverse_iterator(link_type x):node(x)
    {
    }

    __list_reverse_iterator(const self& other):node(other.node)
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
        node=node->prev;
        return *this;
    }

    self operator++(int)
    {
        self ret=*this;
        node=node->prev;
        return ret;
    }

    self& operator--()
    {
        node=node->next;
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



template <class T,class Alloc>
class list;

template <class T,class Alloc>
bool operator==(const list<T,Alloc>& lhs,const list<T,Alloc>& rhs);

template <class T,class Alloc>
bool operator<(const list<T,Alloc>& lhs,const list<T,Alloc>& rhs);

template <class T,class Alloc>
bool operator<=(const list<T,Alloc>& lhs,const list<T,Alloc>& rhs);

template <class T,class Alloc>
bool operator>(const list<T,Alloc>& lhs,const list<T,Alloc>& rhs);

template <class T,class Alloc>
bool operator>=(const list<T,Alloc>& lhs,const list<T,Alloc>& rhs);




template <class T,class Alloc=alloc>
class list
{
public:
/**
 * @brief 每个容器及其迭代器都提供规范的界面用于编译器自动推导
 */
    using value_type=T;
    using pointer=T*;
    using reference=T&;
    using size_type=size_t;
    using difference_type=ptrdiff_t;
    using iterator=__list_iterator<T,T*,T&>;
    using reverse_iterator=__list_reverse_iterator<T,T*,T&>;

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

    list_node_allocator get_allocator()const
    {
        return list_node_allocator();
    }

public:
    list()
    {
        node=alloc_node();
        node->next=node;
        node->prev=node;
    }

    bool empty()const
    {
        return begin()==end();
    }

    iterator begin()const
    {
        return iterator(node->next);
    }

    iterator end()const
    {
        return iterator(node);
    }

    reference front()
    {
        return *begin();
    }

    reference back()
    {
        return *(end()-1);
    }

    size_type size()const
    {
        return 0;
    }

    size_type max_size()const
    {
        return size_type(-1)/sizeof(list_node);
    }

    reverse_iterator rbegin()const
    {
        return reverse_iterator(node->prev);
    }

    reverse_iterator rend()const
    {
        return reverse_iterator(node);
    }

    iterator insert(iterator pos,const T& x)
    {
        link_type __node=pos.node;
        link_type p=create_node(x);
        p->prev=__node->prev;
        p->next=__node;
        __node->prev->next=p;
        __node->prev=p;
        return iterator(p);
    }

    void insert(iterator pos,size_type n,const T& x)
    {
        while(n--)
        {
            insert(pos,x);
        }  
    }

    void insert(iterator pos,iterator first,iterator last)
    {
        for(;first!=last;++first)
        {
            insert(pos,*first);
        }
    }

    void push_back(const T& x)
    {
        insert(end(),x);
    }

    void push_front(const T& x)
    {
        insert(begin(),x);
    }

    void pop_back()
    {
        if(!empty())
        {
            erase(end()-1);
        }
    }

    void pop_front()
    {
        if(!empty())
        {
            erase(begin());
        }
    }

    iterator erase(iterator pos)
    {
        link_type __next=pos.node->next;
        link_type __prev=pos.node->prev;
        __prev->next=__next;
        __next->prev=__prev;
        destroy_node(pos.node);
        return iterator(__next);
    }

    iterator erase(iterator first,iterator last)
    {
        for(;first!=last;first=erase(first));
    }

    void clear();

    void remove(const T& x)
    {
        iterator first=begin();
        iterator last=end();
        while(first!=last)
        {
            if(*first==x)
            {
                first=erase(first);
            }
        }
    }

    template <class PredicateFunction>
    void remove_if(PredicateFunction pred)
    {

    }

    void reverse()
    {

    }

    void sort()
    {

    }

    template <class CompareFunction>
    void sort(CompareFunction comp)
    {

    }

    void split(iterator pos,list& x)
    {

    }

    void split(iterator pos,list& x,iterator i)
    {

    }

    void split(iterator pos,list& x,iterator first,iterator last)
    {

    }

    void swap(list& x)
    {

    }

    void unique()
    {

    }

protected:
    link_type node;

    friend bool operator== <T,Alloc>(const list<T,Alloc>& lhs,const list<T,Alloc>& rhs);
    friend bool operator< <T,Alloc>(const list<T,Alloc>& lhs,const list<T,Alloc>& rhs);
    friend bool operator<= <T,Alloc>(const list<T,Alloc>& lhs,const list<T,Alloc>& rhs);
    friend bool operator> <T,Alloc>(const list<T,Alloc>& lhs,const list<T,Alloc>& rhs);
    friend bool operator>= <T,Alloc>(const list<T,Alloc>& lhs,const list<T,Alloc>& rhs);
};

template <class T,class Alloc>
void list<T,Alloc>::clear()
{
    link_type current=node->next;
    link_type tmp;
    while(current!=node)
    {
        tmp=current;
        current=current->next;
        destroy_node(tmp);
    }
    node->next=node;
    node->prev=node;
}


}

#endif
