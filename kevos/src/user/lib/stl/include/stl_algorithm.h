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

/**
 *@brief since c++17
 */
template <class FowardIterator>
constexpr FowardIterator max_element(FowardIterator first,FowardIterator last)
{
    auto _max=first;
    ++first;
    while(first!=last)
    {
        if(*first>*_max)
            _max=first;
        ++first;
    }
    return _max;
}

/**
 *@brief since c++17
 */
template <class FowardIterator,class Compare>
constexpr FowardIterator max_element(FowardIterator first,FowardIterator last,Compare comp)
{
    auto _max=first;
    ++first;
    while(first!=last)
    {
        if(comp(*_max,*first))
            _max=first;
        ++first;
    }
    return _max;
}

/**
 *@brief since c++17
 */
template <class FowardIterator>
constexpr FowardIterator min_element(FowardIterator first,FowardIterator last)
{
    auto _min=first;
    ++first;
    while(first!=last)
    {
        if(*first<*_min)
            _min=first;
        ++first;
    }
    return _min;
}

/**
 *@brief since c++17
 */
template <class FowardIterator,class Compare>
constexpr FowardIterator min_element(FowardIterator first,FowardIterator last,Compare comp)
{
    auto _min=first;
    ++first;
    while(comp(first,last))
    {
        if(*first<*_min)
            _min=first;
        ++first;
    }
    return _min;
}

/**
 *@brief since c++17
 */
template <class ExecutionPolicy,class ForwardIterator,class Compare>
ForwardIterator max_element(ExecutionPolicy&& policy,ForwardIterator first,ForwardIterator last,Compare comp);

/**
 *@brief since c++17
 */
template <class ExecutionPolicy,class ForwardIterator,class Compare>
ForwardIterator min_element(ExecutionPolicy&& policy,ForwardIterator first,ForwardIterator last,Compare comp);

/**
 *@brief since c++14
 */
template <class T>
constexpr const T& max(const T& a,const T& b)
{
    return a<b?b:a;
}

/**
 *@brief since c++14
 */
template <class T,class Compare>
constexpr const T& max(const T& a,const T& b,Compare comp)
{
    return comp(a,b)?b:a;
}

/**
 *@brief since c++14
 */
template <class T>
constexpr const T& min(const T& a,const T& b)
{
    return a<b?a:b;
}

/**
 *@brief since c++14
 */
template <class T,class Compare>
constexpr const T& min(const T& a,const T& b,Compare comp)
{
    return comp(a,b)?a:b;
}

/**
 *@brief since c++14
 */
template <class T>
constexpr T max(initializer_list<T> ilist)
{
    return *max_element(ilist.begin(),ilist.end());
}

/**
 *@brief since c++14
 */
template <class T>
constexpr T min(initializer_list<T> ilist)
{
    return *min_element(ilist.begin(),ilist.end());
}


/**
 *@brief since c++17
 */
template <class ExecutionPolicy,class ForwardIterator,class T>
ForwardIterator find(ExecutionPolicy&& policy,ForwardIterator first,ForwardIterator last,const T& value);

/**
 *@brief since c++20
 */
template <class InputIterator,class T>
constexpr InputIterator find(InputIterator first,InputIterator last,const T& value)
{
    while(first!=last)
    {
        if(*first==value)
            return first;
        ++first;
    }
    return last;
}

/**
 *@brief since c++17
 */
template <class ExecutionPolicy,class ForwardIterator,class UnaryPredicate>
ForwardIterator find_if(ExecutionPolicy&& policy,ForwardIterator first,ForwardIterator last,UnaryPredicate p);

/**
 *@brief since c++20
 */
template <class InputIterator, class UnaryPredicate>
constexpr InputIterator find_if(InputIterator first,InputIterator last,UnaryPredicate p);

/**
 *@brief since c++17
 */
template <class ExecutionPolicy,class ForwardIterator, class UnaryPredicate>
ForwardIterator find_if_not(ExecutionPolicy&& policy,ForwardIterator first,ForwardIterator last,UnaryPredicate q);

/**
 *@brief since c++20
 */
template <class InputIterator, class UnaryPredicate>
constexpr InputIterator find_if_not(InputIterator first,InputIterator last,UnaryPredicate q);

template<class ForwardIterator,class T>
constexpr void fill(ForwardIterator first,ForwardIterator last,const T& value)
{
    while(first!=last)
    {
        *first++=value;
    }
}


}

#endif
