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

#ifndef _STL_STL_ALGORITHM_H_
#define _STL_STL_ALGORITHM_H_

#include <stl_iterator.h>

#include <cstring>
#include <initializer_list>

namespace std
{

template <class InputIterator,class OutputIterator>
OutputIterator __copy_template(InputIterator first,InputIterator last,OutputIterator result,
                            random_access_iterator_tag input_iter_tag,random_access_iterator_tag output_iter_tag)
{
    memmove(&*result,&*first,sizeof(typename iterator_traits<InputIterator>::value_type)*(last-first));
    return result+(last-first);
}

template <class InputIterator,class OutputIterator>
OutputIterator copy(InputIterator first,InputIterator last,OutputIterator result)
{
    __copy_template
    (
        first,
        last,
        result,
        typename iterator_traits<InputIterator>::iterator_category(),
        typename iterator_traits<InputIterator>::iterator_category()
    );
}


template <class FowardIterator>
FowardIterator max_element(FowardIterator first,FowardIterator last)
{
    FowardIterator _max=first;
    ++first;
    while(first!=last)
    {
        if(*first>*_max)
            _max=first;
        ++first;
    }
    return _max;
}

template <class FowardIterator,class Compare>
FowardIterator max_element(FowardIterator first,FowardIterator last,Compare comp)
{
    FowardIterator _max=first;
    ++first;
    while(first!=last)
    {
        if(comp(*_max,*first))
            _max=first;
        ++first;
    }
    return _max;
}

template <class FowardIterator>
constexpr FowardIterator min_element(FowardIterator first,FowardIterator last)
{
    FowardIterator _min=first;
    ++first;
    while(first!=last)
    {
        if(*first<*_min)
            _min=first;
        ++first;
    }
    return _min;
}

template <class FowardIterator,class Compare>
constexpr FowardIterator min_element(FowardIterator first,FowardIterator last,Compare comp)
{
    FowardIterator _min=first;
    ++first;
    while(comp(first,last))
    {
        if(*first<*_min)
            _min=first;
        ++first;
    }
    return _min;
}


template <class T>
constexpr const T& max(const T& a,const T& b)
{
    return a<b?b:a;
}

template <class T,class Compare>
constexpr const T& max(const T& a,const T& b,Compare comp)
{
    return comp(a,b)?b:a;
}


template <class T>
constexpr const T& min(const T& a,const T& b)
{
    return a<b?a:b;
}

template <class T,class Compare>
constexpr const T& min(const T& a,const T& b,Compare comp)
{
    return comp(a,b)?a:b;
}


template <class T>
constexpr T max(initializer_list<T> ilist)
{
    return *max_element(ilist.begin(),ilist.end());
}

template <class T>
constexpr T min(initializer_list<T> ilist)
{
    return *min_element(ilist.begin(),ilist.end());
}


template <class ExecutionPolicy,class ForwardIt,class Compare>
ForwardIt max_element(ExecutionPolicy&& policy,ForwardIt first,ForwardIt last,Compare comp)
{
    return 0;
}

template <class ExecutionPolicy,class ForwardIt,class Compare>
ForwardIt min_element(ExecutionPolicy&& policy,ForwardIt first,ForwardIt last,Compare comp)
{
    return 0;
}


}

#endif
