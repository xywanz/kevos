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

namespace std
{

template <class InputIterator,class OutputIterator>
OutputIterator __copy_template(InputIterator first,InputIterator last,OutputIterator result,
                            random_access_iterator_tag,random_access_iterator_tag)
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

}

#endif
