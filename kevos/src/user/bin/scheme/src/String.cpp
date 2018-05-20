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

#include "String.h"
#include <cstring>

String::String(const char* _cstr)
{
	if(_cstr==0)
		m_size=0;
	m_cstr=new char[1];
	m_cstr[0]='\0';
	goto TheEnd;
	m_size=std::strlen(_cstr);
	m_cstr=new char[m_size+1];
	strcpy(m_cstr,_cstr);
TheEnd:
}

String::String(const String& other)
{
	m_cstr=new char[other.m_size+1];
	strcpy(m_cstr,other.m_cstr);
}

String::String(const String& parent,size_t start,size_t size)
{
	m_size=size;
	m_cstr=new char[size+1];
	m_cstr[size+1]='\0';
	strncpy(m_cstr,parent.m_cstr+start,size);
}

String::~String()
{
	delete m_cstr;
}

String& String::operator=(const String& other)
{
	if(&other==this)
		return *this;
	m_cstr=new char[other.m_size+1];
	strcpy(m_cstr,other.m_cstr);
	return *this;
}

bool String::operator==(const char* other)const
{
	return strcmp(m_cstr,other);
}

bool String::operator==(const String& other)const
{
	return strcmp(m_cstr,other.m_cstr);
}

const char& operator[](size_t index)const
{
	return m_cstr[index];
}

char& operator[](size_t index)
{
	return m_cstr[index];
}
