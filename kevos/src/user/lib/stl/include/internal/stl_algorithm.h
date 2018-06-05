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

#include <internal/stl_iterator.h>

#include <cstring>
#include <initializer_list>
#include <utility>

namespace std
{


template<class T>
inline T* __copy_t(const T* first,const T* last,T* result)
{
    memmove(result,first,reinterpret_cast<size_t>(last)-reinterpret_cast<size_t>(first));
    return result+(last-first);
}

template<class RandomAccessIterator,class OutputIterator,class Distance>
inline OutputIterator __copy_d(RandomAccessIterator first,RandomAccessIterator last,
                OutputIterator result,Distance*)
{
    for(Distance d=last-first;d>0;--d,++first,++result)
    {
        *result=*first;
    }
    return result;
}

template<class RandomAccessIterator,class OutputIterator>
inline OutputIterator __copy(RandomAccessIterator first,RandomAccessIterator last,
                OutputIterator result,random_access_iterator_tag)
{
    return __copy_d(first,last,result,difference_type(first));
}

template<class InputIterator,class OutputIterator>
inline OutputIterator __copy(InputIterator first,InputIterator last,
                OutputIterator result,input_iterator_tag)
{
    for(;first!=last;++first,++result)
    {
        *result=*first;
    }
    return result;
}

template <class InputIterator,class OutputIterator,class IteratorCategory>
inline OutputIterator __copy_dispatch(InputIterator first,InputIterator last,OutputIterator result,
                            IteratorCategory input_iter_tag)
{
    return __copy(first,last,result,input_iter_tag);
}

template<class T,class IteratorCategory>
inline T* __copy_dispatch(const T* first,const T* last,T* result,random_access_iterator_tag)
{
    return __copy_t(first,last,result);
}

template<class T,class IteratorCategory>
inline T* __copy_dispatch(T* first,T* last,T* result,random_access_iterator_tag)
{
    return __copy_t((const T*)first,(const T*)last,result);
}

template <class InputIterator,class OutputIterator>
inline OutputIterator copy(InputIterator first,InputIterator last,OutputIterator result)
{
    return __copy_dispatch(first,last,result,category(first));
}

inline char* copy(const char* first,const char* last,char* result)
{
    memmove(result,first,last-first);
    return result+(last-first);
}

inline wchar_t* copy(const wchar_t* first,const wchar_t* last,wchar_t* result)
{
    memmove(result,first,reinterpret_cast<size_t>(last)-reinterpret_cast<size_t>(first));
    return result+(last-first);
}




template<class T>
inline T* __copy_backward_dispatch(const T* first,const T* last,T* result)
{
    return __copy_t(first,last,result);
}

template<class T>
inline T* __copy_backward_dispatch(T* first,T* last,T* result)
{
    return __copy_t((const T*)first,(const T*)last,result);
}

template<class RandomAccessIterator,class BidirectionIterator2,class Distance>
inline BidirectionIterator2 __copy_backward(RandomAccessIterator first,RandomAccessIterator last,
                                        BidirectionIterator2 result,Distance*)
{
    --last;
    for(Distance d=last-first;d>0;--d,--last,--result)
    {
        *result=*last;
    }
    return last;
}

template<class RandomAccessIterator,class BidirectionIterator2>
inline BidirectionIterator2 __copy_backward(RandomAccessIterator first,RandomAccessIterator last,
                                        BidirectionIterator2 result,random_access_iterator_tag)
{
    return __copy_backward_d(first,last,result,difference_type(first));
}

template<class BidirectionIterator1,class BidirectionIterator2>
inline BidirectionIterator2 __copy_backward(BidirectionIterator1 first,BidirectionIterator1 last,
                                        BidirectionIterator2 result,bidirection_iterator_tag)
{
    for(--last;last!=first;--last,--result)
    {
        *result=*last;
    }
    *result=*last;
    return --result;
}

template<class BidirectionIterator1,class BidirectionIterator2>
inline BidirectionIterator2 __copy_dispatch(BidirectionIterator1 first,BidirectionIterator1 last,
                                            BidirectionIterator2 result)
{
    return __copy_backward(first,last,result,category(first));    
}

template<class BidirectionIterator1,class BidirectionIterator2>
inline BidirectionIterator2 copy_backward(BidirectionIterator1 first,BidirectionIterator1 last,
                                            BidirectionIterator2 result)
{
    return __copy_backward_dispatch(first,last,result);
}



template<class RandomAccessIterator,class OutputIterator,class UnaryPredicate,class Distance>
inline OutputIterator __copy_if_d(RandomAccessIterator first,RandomAccessIterator last,
                        OutputIterator result,UnaryPredicate p,Distance*)
{
    for(Distance d=last-first;d>0;++first)
    {
        if(p(first))
            *result++=*first;
    }
    return result;
}

template<class InputIterator,class OutputIterator,class UnaryPredicate>
inline OutputIterator __copy_if(InputIterator first,InputIterator last,
                        OutputIterator result,UnaryPredicate p,input_iterator_tag)
{
    for(;first!=last;++first)
    {
        if(p(first))
            *result++=*first;
    }
    return result;
}

template<class RandomAccessIterator,class OutputIterator,class UnaryPredicate>
inline OutputIterator __copy_if(RandomAccessIterator first,RandomAccessIterator last,
                        OutputIterator result,UnaryPredicate p,random_access_iterator_tag)
{
    return __copy_if_d(first,last,result,p,difference_type(first));
}

template<class InputIterator,class OutputIterator,class UnaryPredicate>
inline OutputIterator copy_if(InputIterator first,InputIterator last,OutputIterator result,UnaryPredicate p)
{
    return __copy_if(first,last,result,p,category(first));
}





/**
 *@brief since c++17
 */
template <class ForwardIterator>
constexpr ForwardIterator max_element(ForwardIterator first,ForwardIterator last)
{
    auto _max=first;
    ++first;
    for(;first!=last;++first)
    {
        if(*first>*_max)
            _max=first;
    }
    return _max;
}

/**
 *@brief since c++17
 */
template <class ForwardIterator,class Compare>
constexpr ForwardIterator max_element(ForwardIterator first,ForwardIterator last,Compare comp)
{
    auto _max=first;
    ++first;
    for(;first!=last;++first)
    {
        if(comp(*_max,*first))
            _max=first;
    }
    return _max;
}

/**
 *@brief since c++17
 */
template <class ForwardIterator>
constexpr ForwardIterator min_element(ForwardIterator first,ForwardIterator last)
{
    auto _min=first;
    ++first;
    for(;first!=last;++first)
    {
        if(*first<*_min)
            _min=first;
    }
    return _min;
}

/**
 *@brief since c++17
 */
template <class ForwardIterator,class Compare>
constexpr ForwardIterator min_element(ForwardIterator first,ForwardIterator last,Compare comp)
{
    auto _min=first;
    ++first;
    for(;first!=last;++first)
    {
        if(comp(*first,*_min))
            _min=first;
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
    for(;first!=last;++first)
    {
        if(*first==value)
            return first;
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
constexpr InputIterator find_if(InputIterator first,InputIterator last,UnaryPredicate p)
{
    for(;first!=last;++first)
    {
        if(p(first))
            return first;
    }
    return last;
}

/**
 *@brief since c++17
 */
template <class ExecutionPolicy,class ForwardIterator, class UnaryPredicate>
ForwardIterator find_if_not(ExecutionPolicy&& policy,ForwardIterator first,ForwardIterator last,UnaryPredicate q);

/**
 *@brief since c++20
 */
template <class InputIterator, class UnaryPredicate>
constexpr InputIterator find_if_not(InputIterator first,InputIterator last,UnaryPredicate q)
{
    for(;first!=last;++first)
    {
        if(!p(first))
            return first;
    }
    return last;
}

template<class ForwardIterator,class T>
constexpr void fill(ForwardIterator first,ForwardIterator last,const T& value)
{
    for(;first!=last;++first)
    {
        *first=value;
    }
}

template<class ForwardIterator,class T>
constexpr void fill_n(ForwardIterator first,size_t n,const T& value)
{
    for(;n>0;--n,++first)
    {
        *first=value;
    }
}


template<class ExecutionPolicy,class ForwardIterator,class UnaryFunction>
constexpr void for_each(ExecutionPolicy&& policy,ForwardIterator first,ForwardIterator last,UnaryFunction f);

template<class InputIterator,class UnaryFunction>
constexpr UnaryFunction for_each(InputIterator first,InputIterator last,UnaryFunction f)
{
    for(;first!=last;++first)
        f(*first);
    return f;
}


template<class ExecutionPolicy,class ForwardIterator,class Size,class UnaryFunction>
constexpr ForwardIterator for_each_n(ExecutionPolicy&& policy,ForwardIterator first,Size n,UnaryFunction f);

template<class InputIterator,class Size,class UnaryFunction>
constexpr InputIterator for_each_n(InputIterator first,Size n,UnaryFunction f)
{
    for(;n>0;--n,++first)
        f(*first);
    return first;
}



}

#endif
