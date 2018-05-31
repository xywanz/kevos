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

#ifndef _KEVOS_TOOL_SCHEME_VAR_LIST_H_
#define _KEVOS_TOOL_SCHEME_VAR_LIST_H_

#include "String.h"


class VarList
{
public:
	struct Var
	{
		String symbol;
		void* val;
		Var* next;
		Node(const String& _symbol,void* _val,Var* _next=nullptr)
			:symbol(_symbol),val(_val),next(_next)
		{
		}
	};


};


#endif