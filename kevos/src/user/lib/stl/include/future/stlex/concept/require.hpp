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

#ifndef _STLEX_CONCEPT_REQUIRE_HPP_
#define _STLEX_CONCEPT_REQUIRE_HPP_

#include <utility>

namespace stlex
{

#define concept_signed_member_method(MemberMethod)                                                  \
template<class __Type,class ...Args>                                                                     \
struct has_signed_member_method_##MemberMethod##_helper                                             \
{                                                                                                   \
private:                                                                                            \
    template<class __U,class = decltype(std::declval<__U>().MemberMethod(std::declval<Args>()...))>     \
    static std::true_type test(int);                                                                \
    template<class U>                                                                               \
    static std::false_type test(...);                                                               \
public:                                                                                             \
    using type=decltype(test<__Type>(0));                                                                \
};                                                                                                  \
template<class __Type,class ...Args>                                                                     \
struct has_signed_member_method_##MemberMethod : public has_signed_member_method_##MemberMethod##_helper<__Type,Args...>::type {};


#define concept_member_method(MemberMethod)                                                         \
template<class __Type,class = void>                                                                      \
struct has_member_method_##MemberMethod : public std::false_type {};                                \
template<class __Type>                                                                                   \
struct has_member_method_##MemberMethod <__Type,std::void_t<decltype(&__Type::MemberMethod)>> : public std::true_type {};


#define concept struct

#define require_member_method(MemberMethod)   \
static_assert(has_member_method_##MemberMethod <T>::value,"member method not found");

#define require_signed_member_method(T,MemberMethod,...)    \
static_assert(has_signed_member_method_##MemberMethod <T,...>::value,"signed member method not found");

}


#endif
