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

#ifndef _STL_STL_ARRAY_H_
#define _STL_STL_ARRAY_H_

#include <stl_uninitialized.h>

#include <initializer_list>

namespace std
{

template <class T,class Pointer,class Reference>
class __array_reverse_iterator;


template <class T,size_t N>
class array
{
public:

    using value_type=T;
    using pointer=T*;
    using reference=T&;
    using iterator=T*;
    using const_iterator=const T*;
    using reverse_iterator=__array_reverse_iterator<T,T*,T&>;
    using const_reverse_iterator=__array_reverse_iterator<T,T*,T&>;
    using different_type=ptrdiff_t;
    using size_type=size_t;


    array()
    {
    }

    array(const initializer_list<T>& _lst)
    {
        uninitialized_copy(_lst.begin(),_lst.end(),m_arr);
    }

    bool empty()const
    {
        return false;
    }

    iterator begin()
    {
        return m_arr;
    }

    const_iterator cbegin()const
    {
        return m_arr;
    }

    iterator end()
    {
        return m_arr+N;
    }

    const_iterator cend()const
    {
        return m_arr+N;
    }

    reverse_iterator rbegin()
    {
        return end()-1;
    }

    reverse_iterator rend()
    {
        return begin()-1;
    }

    const_reverse_iterator crbegin()const
    {
        return reverse_iterator((pointer)(m_arr+N-1));
    }

    const_reverse_iterator crend()const
    {
        return reverse_iterator((pointer)(m_arr-1));
    }
 
    pointer data()
    {
        return m_arr;
    }

    const T* data()const
    {
        return (const T*)m_arr;
    }

    reference front()
    {
        return m_arr[0];
    }

    const T& front()const
    {
        return (const T&)m_arr[0];
    }

    reference back()
    {
        return m_arr[N-1];
    }

    const T& back()const
    {
        return (const T&)m_arr[N-1];
    }

    reference at(size_type n)
    {
        if(n<size())
            return m_arr[n];
    }

    const T& at(size_type n)const
    {
        if(n<size())
            return (const T&)m_arr[n];        
    }

    reference operator[](size_type n)
    {
        return m_arr[n];
    }

    const T& operator[](size_type n)const
    {
        return (const T&)m_arr[n];
    }

    size_type max_size()const
    {
        return size_type(-1)/sizeof(T);
    }

    size_type size()const
    {
        return N;
    }

    void fill(const T& x)
    {
        destroy(begin(),end());
        uninitialized_fill_n(m_arr,size(),x);
    }

    void swap(array& x)
    {

    }

protected:
    T m_arr[N];
};

template <class T>
class array<T,0>
{
public:
    bool empty()const
    {
        return true;
    }
};



template <class T,class Pointer,class Reference>
class __array_reverse_iterator
{
protected:
    using forward_iterator=T*;
public:
    using iterator_category=random_access_iterator_tag;
    using value_type=T;
    using pointer=Pointer;
    using reference=Reference;
    using size_type=size_t;
    using difference_type=ptrdiff_t;
    using iterator=__array_reverse_iterator<T,Pointer,Reference>;
    using const_iterator=__array_reverse_iterator<T,const T*,const T&>;

    using self=__array_reverse_iterator;

    __array_reverse_iterator()
    {
    }

    __array_reverse_iterator(forward_iterator i):iter(i)
    {
    }

    __array_reverse_iterator(const __array_reverse_iterator& other):iter(other.iter)
    {
    }

    bool operator==(const __array_reverse_iterator& other)const
    {
        return iter==other.iter;
    }

    bool operator!=(const __array_reverse_iterator& other)const
    {
        return iter!=other.iter;
    }

    bool operator<(const __array_reverse_iterator& other)const
    {
        return iter<other.iter;
    }

    bool operator<=(const __array_reverse_iterator& other)const
    {
        return iter<=other.iter;
    }

    bool operator>(const __array_reverse_iterator& other)const
    {
        return iter>other.iter;
    }

    bool operator>=(const __array_reverse_iterator& other)const
    {
        return iter>=other.iter;
    }

    reference operator*()const
    {
        return *iter;
    }

    pointer operator->()const
    {
        return &(operator*());
    }

    self& operator++()
    {
        --iter;
        return *this;
    }

    self operator++(int)
    {
        self ret=*this;
        --iter;
        return ret;
    }

    self& operator--()
    {
        ++iter;
        return *this;
    }

    self operator--(int)
    {
        self ret=*this;
        ++iter;
        return ret;
    }

    self operator+(difference_type n)
    {
        return iter-n;
    }

    self operator-(difference_type n)
    {
        return iter+n;
    }

    self& operator+=(difference_type n)
    {
        iter-=n;
        return *this;
    }

    self& operator-=(difference_type n)
    {
        iter+=n;
        return *this;
    }

protected:
    forward_iterator iter;
};

}

#endif
