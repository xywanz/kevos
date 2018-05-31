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

#ifndef _STL_STL_ALLOC_
#define _STL_STL_ALLOC_

#include <cstddef>
#include <stl_construct.h>
#include <cstdlib>
#include <climits>

namespace std
{

template <int inst>
class __malloc_alloc_template
{
public:
    typedef void (*__handler)();
private:
    static void* oom_malloc(size_t n);
    static void* oom_realloc(void* p,size_t n);
    static __handler __malloc_alloc_oom_handler;
public:
    static void* allocate(size_t n)
    {
        void* ret=malloc(n);
        if(!ret)
            ret=oom_malloc(n);
        return ret;
    }

    static void deallocate(void* p,size_t)
    {
        free(p);
    }

    static void reallocate(void* p,size_t n)
    {
        void* ret=realloc(p,n);
        if(!ret)
            ret=oom_realloc(p,n);
        return ret;
    }

    static __handler set_malloc_handler(__handler new_handler)
    {
        __handler old=__malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler=new_handler;
        return old;
    }
};

template <int inst>
__handler __malloc_alloc_template<inst>::__malloc_alloc_oom_handler=0;

template <int inst>
void* __malloc_alloc_template<inst>::oom_malloc(size_t n)
{
    void* ret;
    while(1)
    {
        __malloc_alloc_oom_handler();
        ret=malloc(n);
        if(ret)
            return ret;
    }
}

template <int inst>
void __malloc_alloc_template<inst>::oom_realloc(void* p,size_t n)
{
    void* ret;
    while(1)
    {
        __malloc_alloc_oom_handler();
        ret=realloc(p,n);
        if(ret)
            return ret;
    }
}

typedef __malloc_alloc_template<0> malloc_alloc;



template <int inst>
class __default_alloc_template
{
private:
    enum {__ALIGN=8};
    enum {__MAX_BYTES=128};
    enum {__NFREELIST=__MAX_BYTES/__ALIGN};

    static size_t round_up(size_t bytes)
    {
        return (bytes+__ALIGN-1)&(~(__ALIGN-1));
    }

    union obj
    {
        union obj* next;
        char client_data[1];
    }

    static obj* volatile free_list[__NFREELIST];

    static free_list_index(size_t byte)
    {
        return (bytes+__ALIGN-1)/__ALIGN-1;
    }
    
    static void* refill(size_t n);

    static char* chunk_alloc(size_t size,int& nobjs);

    static char* free_start;
    static char* free_end;
    static size_t heap_size;

public:
    static void* allocate(size_t n)
    {
        if(n>(size_t)__MAX_BYTES)
            return malloc_alloc::allocate(n);
        obj* volatile *dst_free_list=free_list+free_list_index(n);
        obj* ret=*my_free_list;
        if(!obj)
        {
            void* r=refill(round_up(n));
            return r;
        }
        *my_free_list=ret->next;
        return ret;
    }

    static void deallocate(void* p,size_t n)
    {
        if(n>(size_t)__MAX_BYTES)
            free(p);
        obj* volatile* my_free_list=free_list+free_list_index(n);
        obj* released=(obj*)p;
        released->next=*my_free_list;
        *my_free_list=released;
    }

    static void* reallocate(void* p,size_t old_sz,size_t new_sz)
    {

    }

};

template <int inst>
__default_alloc_template<inst>::obj* volatile 
__default_alloc_template<inst>::free_list[__NFREELIST]=
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

template <int inst>
char* __default_alloc_template<inst>::free_start=0;

template <int inst>
char* __default_alloc_template<inst>::free_end=0;

template <int inst>
size_t __default_alloc_template<inst>::heap_size=0;


template <int inst>
void* __default_alloc_template<inst>::refill(size_t n)
{
    int nobjs=20;
    char* chunk=chunk_alloc(n,nobjs);
    if(1==nobjs)
        return chunk;
    obj* volatile* my_free_list=free_list+free_list_index(n);
    obj* ret=(obj*)chunk;
    obj* current,next;
    *my_free_list=next=(obj*)(chunk+n);
    for(size_t i=1;;++i)
    {
        current=next;
        next=(obj*)((char*)next+n);
        if(nobjs-1==i)
        {
            current->next=0;
            break;
        }
        else
        {
            current->next=next;
        }
    }
    return ret;
}

template <int inst>
char* __default_alloc_template<inst>::chunk_alloc(size_t size,int& nobjs)
{
    char* ret;
    size_t total=size*nobjs;
    size_t rest=free_end-free_start;
    if(rest>=total)
    {
        ret=free_start;
        free_start+=total;
        return ret;
    }
    else if(rest>=size)
    {
        nobjs=rest/size;
        total=size*nobjs;
        ret=free_start;
        free_start+=total;
        return ret;    
    }
    else
    {
        obj* volatile *my_free_list;
        if(rest>0)
        {
            my_free_list=free_list+free_list_index(rest);
            ((obj*)free_start)->next=*my_free_list;
            *my_free_list=(obj*)free_start;
        }
        size_t bytes_to_get=2*total+round_up(heap_size>>4);
        free_start=(char*)malloc(bytes_to_get);
        if(!free_start)
        {
            for(size_t i=size;i<__MAX_BYTES;i+=__ALIGN)
            {
                my_free_list=free_list+free_list_index(i);
                obj* p=*my_free_list;
                if(p)
                {
                    *my_free_list=p->next;
                    free_start=(char*)p;
                    free_end=free_start+i;
                    return chunk_alloc(size,nobjs);
                }
            }
            free_end=0;
            free_start=(char*)malloc_alloc::allocate(bytes_to_get);
        }
        heap_size+=bytes_to_get;
        free_end=free_start+bytes_to_get;
        return chunk_alloc(size,nobjs);
    }
}


template <class T,class Alloc>
class simple_alloc
{
public:
    static T* allocate(size_t n)
    {
        return n?(T*)Alloc::allocate(n*sizeof(T)):0;
    }

    static T* allocate()
    {
        return Alloc::allocate(sizeof(T));
    }

    static void deallocate(T* p,size_t n)
    {
        if(n)
            Alloc::deallocate(p,n*sizeof(T));
    }

    static void deallocate(T* p)
    {
        Alloc::deallocate(p,sizeof(T));
    }
};

using alloc=__default_alloc_template<0>;

}


#endif
