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

#ifndef _STL_TYPE_TRAITS_H_
#define _STL_TYPE_TRAITS_H_

#include <stl_iterator.h>

namespace std
{

struct __true_type {};
struct __false_type {};

template <class T>
struct type_traits
{
    using has_trival_default_constructor=__false_type;
    using has_trival_copy_constructor=__false_type;
    using has_trival_assignment_operator=__false_type;
    using has_trival_destructor=__false_type;
    using is_POD_type=__false_type;
};

template <class T>
struct type_traits<T*>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

template <>
struct type_traits<char>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

template <>
struct type_traits<unsigned char>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

template <>
struct type_traits<short>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

template <>
struct type_traits<unsigned short>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

template <>
struct type_traits<int>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

template <>
struct type_traits<unsigned int>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

template <>
struct type_traits<long>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

template <>
struct type_traits<unsigned long>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

template <>
struct type_traits<long long>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

template <>
struct type_traits<unsigned long long>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

template <>
struct type_traits<float>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

template <>
struct type_traits<double>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

template <>
struct type_traits<long double>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

template <>
struct type_traits<bool>
{
    using has_trival_default_constructor=__true_type;
    using has_trival_copy_constructor=__true_type;
    using has_trival_assignment_operator=__true_type;
    using has_trival_destructor=__true_type;
    using is_POD_type=__true_type;
};

}

#endif