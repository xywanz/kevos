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

/*****************************************************************************
*  @file     bitmap.h                            
*  @brief    位图                 
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
*****************************************************************************/

#ifndef _KEVOS_KERNEL_COMMON_BITMAP_H_
#define _KEVOS_KERNEL_COMMON_BITMAP_H_

#include <sys/portable.h>
#include <arch/common/types.h>

KEVOS_NSS_3(kevos,kernel,common);

#define DynamicBitmap	0


template<size_t byteCount,class ByteType=unsigned char>
class Bitmap
{
public:
	Bitmap()
	{
		for(size_t i=0;i<byteCount;++i)
			m_bitmap[i]=0;
	}

	bool set(size_t index)
	{
		ByteType mask=1<<bitIndexOf(index);
		bool retVal=m_bitmap[byteIndexOf(index)]&mask;
		m_bitmap[byteIndexOf(index)]|=mask;
		return retVal;
	}

	bool unset(size_t index)
	{
		ByteType mask=1<<bitIndexOf(index);
		bool retVal=m_bitmap[byteIndexOf(index)]&mask;
		m_bitmap[byteIndexOf(index)]&=(~mask);
		return retVal;
	}

	bool get(size_t index)const
	{
		return m_bitmap[byteIndexOf(index)]&(1<<bitIndexOf(index));
	}

private:
	static constexpr size_t s_bitsPerByte=sizeof(ByteType)*8;
	ByteType m_bitmap[byteCount];
	size_t m_size;

	static constexpr size_t bitIndexOf(size_t bit)
	{
		return bit%s_bitsPerByte;
	}

	static constexpr size_t byteIndexOf(size_t bit)
	{
		return bit/s_bitsPerByte;
	}
};


template<class ByteType>
class Bitmap<DynamicBitmap,ByteType>
{
public:
	Bitmap(ByteType* bitmap,size_t size);

	bool set(size_t index);

	bool unset(size_t index);

	bool get(size_t index)const;

private:
	static constexpr size_t s_bitsPerByte=sizeof(ByteType)*8;
	ByteType* m_bitmap;
	size_t m_size;

	static size_t bitIndexOf(size_t bit)
	{
		return bit%s_bitsPerByte;
	}

	static size_t byteIndexOf(size_t bit)
	{
		return bit/s_bitsPerByte;
	}
};

KEVOS_NSE_3(common,kernel,kevos);

#endif
