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

#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C"{
#endif

void* memcpy(void* dst,const void* src,size_t count);
void* memset(void* s,int ch,size_t n);
void* memmove(void* dst,const void* src,size_t count);

size_t strlen(const char * str);
int strcmp(const char *s1,const char *s2);
char *strcat(char *dst,const char *src);
char *strcpy(char *dst,const char *src);
char *strchr(char *str,char c);

char *strncpy(char *dst,const char *src,size_t n);
int strncmp(const char *s1,const char *s2,int maxlen);
char *strnset(char *str,char c,size_t n);

#ifdef __cplusplus
}
#endif

#endif
