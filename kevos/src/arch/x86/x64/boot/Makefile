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

POBJ = ../../../../../../build/tmp
PINC = ../../../../../include
PSTDINC = ../../../../user/lib/stdlib/include/stdinc
PSTDINCXX = ../../../../user/lib/stdlib/include/stdinc++
PSTLINC = ../../../../user/lib/stl/include

CC = gcc-7
CCFLAGS = -m64 -std=c11 -fno-builtin -nostdinc -nostdlib -I$(PINC) -I$(PSTDINC) -O0 -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $(POBJ)/$@ -c $<
CXX = g++-7
CXXFLAGS = -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I$(PSTDINCXX) -I$(PSTDINC) -I$(PINC) -I$(PSTLINC) -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $(POBJ)/$@ -c $<
ASM = g++-7
ASMFLAGS = $(CXXFLAGS)

out: boot.32.cpp.S boot.32.cpp.S.o boot.64.cpp.o

boot.32.cpp.S: boot.32.cpp
	g++-7 -S -c -m32 -o $(POBJ)/boot.32.cpp.S -fno-builtin -nostdinc -nostdinc++ -nostdlib -I$(PINC) -I$(PSTDINCXX) -I$(PSTDINC) -I$(PSTLINC) -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding boot.32.cpp

boot.32.cpp.S.o: boot.32.cpp.S
	g++-7 -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I$(PINC) -I$(PSTDINCXX) -I$(PSTDINC) -I$(PSTLINC) -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $(POBJ)/boot.32.cpp.S.o $(POBJ)/boot.32.cpp.S

boot.64.cpp.o: boot.64.cpp
	g++-7 -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I$(PINC) -I$(PSTDINCXX) -I$(PSTDINC) -I$(PSTLINC) -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $(POBJ)/boot.64.cpp.o boot.64.cpp
