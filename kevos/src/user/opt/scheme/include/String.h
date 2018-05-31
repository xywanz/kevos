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

#ifndef _KEVOS_TOOL_SCHEME_STRING_H_
#define _KEVOS_TOOL_SCHEME_STRING_H_


class String
{
public:
	String(const char* _cstr=0);
	String(const String& other);
	~String();
	String& operator=(const char* other);
	String& operator=(const String& other);
	bool operator==(const char* other)const;
	bool operator==(const String& other)const;

	const char& operator[](size_t index)const;
	char& operator[](size_t index);

	String subString(size_t start,size_t size){return new String(m_cstr,start,size);}
private:
	String(const String& parent,size_t start,size_t size);
private:
	char* m_cstr;
	size_t m_size;
};


bool operator==(const char* lhs,const String& rhs)
{
	return rhs==lhs;
}


#endif