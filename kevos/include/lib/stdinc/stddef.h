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

#ifndef _STDDEF_H
#define _STDDEF_H


#ifndef _SIZE_T
#define _SIZE_T
using size_t=unsigned long;
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
using ptrdiff_t=long;
#endif

#ifndef __cplusplus
#ifndef _WCHAR_T
#define _WCHAR_T
using wchar_t=short;
#endif
#endif

#define NULL 0

#define offsetof(type,member) ((size_t)&(((type*)0)->member))

#endif