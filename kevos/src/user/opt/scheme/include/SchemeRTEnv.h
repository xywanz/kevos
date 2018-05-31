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

#ifndef _KEVOS_TOOL_SCHEME_SCHEME_RT_ENV_H_
#define _KEVOS_TOOL_SCHEME_SCHEME_RT_ENV_H_

#include "VarList.h"


class SchemeRTEnv
{
public:
	SchemeRTEnv(VarList *_varlist,SchemeRTEnv* _parent);
	void* lookup(const String& _symbol);
	void* set(const String& _symbol,void* _val);
public:
	VarList* varlist;
	SchemeRTEnv* parent;
};


#endif