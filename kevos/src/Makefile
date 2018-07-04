# Copyright 2018 kevin Lau (http://github.com/stormycatcat)
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================


POBJ = ../../build/tmp

OBJ := $(wildcard $(POBJ)/*.o)

LD = g++
LDFLAGS = -Wl,-z -Wl,max-page-size=0x100 -Wl,-melf_x86_64 -Wl,-T -Wl,$(POBJ)/../lds/x64/kernel-ld-script.ld -o $(POBJ)/kernel.bin -m64 -nostdinc -nostdinc++ -nostdlib -mcmodel=kernel -Wl,--start-group $(OBJ) -Wl,--end-group

kernel.bin:
	$(LD) $(LDFLAGS)

all:
	make -C arch/common
	make -C arch/x86/common
	make -C arch/x86/x64
	make -C arch/x86/x64/boot

	make -C kernel
	make -C kernel/utils
	make -C kernel/multitask
	make -C kernel/drivers
	make -C kernel/fs
	make -C kernel/mm
	make -C kernel/net

	make -C user/lib/stdlib/src/cxx
	make -C user/lib/stdlib/src/cxx/cmath
	make -C user/lib/stdlib/src/cxx/cstdio
	make -C user/lib/stdlib/src/cxx/cstdlib
	make -C user/lib/stdlib/src/cxx/cstring

	make -C user/lib/stdlib/src/c
	make -C user/lib/stdlib/src/c/math
	make -C user/lib/stdlib/src/c/stdio
	make -C user/lib/stdlib/src/c/stdlib
	make -C user/lib/stdlib/src/c/string

	make -C test

	make

.PHONY:clean
clean:
	rm -rf $(OBJ) $(POBJ)/kernel.bin