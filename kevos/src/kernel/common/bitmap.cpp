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

#include <kernel/common/bitmap.h>

KEVOS_NSS_2(kernel,common);

template<class ByteType>
Bitmap<DynamicBitmap,ByteType>::Bitmap(ByteType* bitmap,size_t size)
	:m_bitmap(bitmap),m_size(size)
{
	for(size_t i=0;i<size;++i)
	{
		bitmap[i]=0;
	}
}

template<class ByteType>
bool Bitmap<DynamicBitmap,ByteType>::set(size_t index)
{
	size_t bitOffset=bitIndexOf(index);
	size_t byteOffset=byteIndexOf(index);
	ByteType mask=1<<bitOffset;
	bool retVal=m_bitmap[byteOffset]&mask;
	m_bitmap[byteOffset]|=mask;
	return retVal;
}

template<class ByteType>
bool Bitmap<DynamicBitmap,ByteType>::unset(size_t index)
{
	size_t bitOffset=bitIndexOf(index);
	size_t byteOffset=byteIndexOf(index);
	ByteType mask=1<<bitOffset;
	bool retVal=m_bitmap[byteOffset]&mask;
	m_bitmap[byteOffset]&=(~mask);
	return retVal;
}

template<class ByteType>
bool Bitmap<DynamicBitmap,ByteType>::get(size_t index)const
{
	return m_bitmap[byteIndexOf(index)]&(1<<bitIndexOf(index));
}

KEVOS_NSE_2(common,kernel);
