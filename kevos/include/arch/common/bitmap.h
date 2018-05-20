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

#ifndef _KEVOS_ARCH_COMMON_BITMAP_H_
#define _KEVOS_ARCH_COMMON_BITMAP_H_

#include <sys/portable.h>
#include <arch/common/types.h>

KEVOS_NSS(kevos,arch,common);


#define DynamicBitMap	0


template<size_t ByteCount,class ByteType=uint8_t>
class Bitmap
{
public:
	Bitmap():
		m_bitmap({0})
	{
	}
	bool set(size_t index);
	bool unset(size_t index);
	bool get(size_t index);
private:
	ByteType m_bitmap[ByteCount];
	size_t m_size;
};


template<class ByteType>
class Bitmap<DynamicBitMap,ByteType>
{
private:
	ByteType* m_bitmap;
	size_t m_size;
};


KEVOS_NSE(common,arch,kevos);

#endif