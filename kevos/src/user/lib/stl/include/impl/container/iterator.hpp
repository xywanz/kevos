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

#ifndef _STL_ITERATOR_HPP_
#define _STL_ITERATOR_HPP_

#include <cstddef>

namespace std
{

/**
 * @brief 输入迭代器
 */
struct input_iterator_tag
{
};

/**
 * @brief 输出迭代器
 */
struct output_interator_tag
{
};

/**
 * @brief 前向迭代器
 */
struct forward_interator_tag : public input_iterator_tag
{
};

/**
 * @brief 双向迭代器
 */
struct bidirection_iterator_tag : public forward_interator_tag
{
};

/**
 * @brief 随机访问迭代器
 */
struct random_access_iterator_tag : public bidirection_iterator_tag
{
};

/**
 * @brief 迭代器特性萃取
 *
 * 通过这个特性萃取机，可以尽可能少地暴露容器内部细节而实现一套通用的容器算法
 * 每个迭代器都必须提供：1、迭代器种类 2、值类型 3、指针类型 4、引用类型 5、迭代器差类型 6、尺度类型
 */
template <class I>
struct iterator_traits
{
    using iterator_category=typename I::iterator_category;
    using value_type=typename I::value_type;
    using pointer=typename I::pointer;
    using reference=typename I::reference;
    using difference_type=typename I::difference_type;
    using size_type=typename I::size_type;
};

/**
 * @brief 指针也是一种迭代器，属于随机访问类型的迭代器
 */
template <class T>
struct iterator_traits<T*>
{
    using iterator_category=random_access_iterator_tag;
    using value_type=T;
    using pointer=T*;
    using reference=T&;
    using difference_type=ptrdiff_t;
    using size_type=size_t;
};
/**
 * @brief 常量指针
 */
template <class T>
struct iterator_traits<const T*>
{
    using iterator_category=random_access_iterator_tag;
    using value_type=T;
    using pointer=const T*;
    using reference=const T&;
    using difference_type=ptrdiff_t;
    using size_type=size_t;
};

/**
 * @brief 迭代器标准，只是提供一个模板
 *
 * 迭代器是对访问容器方法的一个抽象，只要容器提供了符合规格的迭代器便可以使用通用算法
 * 
 */
template <class Category,class T,class Pointer=T*,class Reference=T&,class SizeType=size_t,class DistanceType=ptrdiff_t>
class iterator
{
public:
    using iterator_category=Category;
    using value_type=T;
    using pointer=Pointer;
    using reference=Reference;
    using size_type=SizeType;
    using difference_type=DistanceType;
};

/**
 * @brief 获取迭代器类型，返回一个迭代器类型的实例
 */
template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category category(const Iterator&)
{
    using Category=typename iterator_traits<Iterator>::iterator_category;
    return Category();
}

/**
 * @brief 获取迭代器值类型，返回一个值的空指针
 */
template <class Iterator>
inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator&)
{
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

/**
 * @brief 返回迭代器的差类型指针
 */
template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type* difference_type(const Iterator&)
{
    return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

/**
 * @brief 返回迭代器的尺度类型指针
 */
template <class Iterator>
inline typename iterator_traits<Iterator>::size_type* size_type(const Iterator&)
{
    return static_cast<typename iterator_traits<Iterator>::size_type*>(0);
}



}

#endif
