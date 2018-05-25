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

LD = ld
LDFLAGS = -z max-page-size=0x1000 -T $(POBJ)/../lds/x64/kernel-ld-script.ld -o $(POBJ)/kernel.bin

OBJ := $(wildcard $(POBJ)/*.o)

kernel.bin:
	$(LD) $(LDFLAGS) $(OBJ)

all:
	make -C arch/common
	make -C arch/x86_64/common
	make -C arch/x86_64/x64
	make -C arch/x86_64/x64/boot

	make -C kernel
	make -C kernel/common
	make -C kernel/drivers
	make -C kernel/fs
	make -C kernel/mm
	make -C kernel/net

	make -C user/lib/stdlib
	make -C user/lib/stdlib/stdio
	make -C user/lib/stdlib/stdlib
	make -C user/lib/stdlib/string

	make

.PHONY:clean
clean:
	rm -rf $(OBJ) $(POBJ)/kernel.bin