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

#ifndef _STL_STL_ITERATOR_H_
#define _STL_STL_ITERATOR_H_

#include <cstddef>

namespace std
{

struct input_iterator_tag{};
struct output_interator_tag{};
struct forward_interator_tag : public input_iterator_tag{};
struct bidirection_iterator_tag : public forward_interator_tag{};
struct random_access_iterator_tag : public bidirection_iterator_tag{};

template <class I>
struct iterator_traits
{
    using iterator_category=typename I::iterator_category;
    using value_type=typename I::value_type;
    using difference_type=typename I::difference_type;
    using pointer=typename I::pointer;
    using reference=typename I::reference;
};

template <class T>
struct iterator_traits<T*>
{
    using iterator_category=random_access_iterator_tag;
    using value_type=T;
    using difference_type=ptrdiff_t;
    using pointer=T*;
    using reference=T&;
};

template <class T>
struct iterator_traits<const T*>
{
    using iterator_category=random_access_iterator_tag;
    using value_type=T;
    using difference_type=ptrdiff_t;
    using pointer=const T*;
    using reference=const T&;
};


template <class Category,class T,class Distance=ptrdiff_t,class Pointer=T*,class Reference=T&>
class iterator
{
    using iterator_category=Category;
    using value_type=T;
    using difference_type=ptrdiff_t;
    using pointer=Pointer;
    using reference=Reference;
};


template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category category(const Iterator&)
{
    using Category=typename iterator_traits<Iterator>::iterator_category;
    return Category();
}

template <class Iterator>
inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator&)
{
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type* difference_type(const Iterator&)
{
    return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}



}

#endif
