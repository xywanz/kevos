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

POBJ = ../../../../build/tmp
PINC = ../../../include
PSTDINC = ../../user/lib/stdlib/include/stdinc
PSTDINCXX = ../../user/lib/stdlib/include/stdinc++

CC = gcc-7
CCFLAGS = -m64 -fno-builtin -nostdinc -nostdlib -I$(PINC) -I$(PSTDINC) -O0 -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $(POBJ)/$@ -c $<
CXX = g++-7
CXXFLAGS = -m64 -fno-builtin -nostdinc -nostdinc++ -nostdlib -I$(PINC) -I$(PSTDINCXX) -I$(PSTDINC) -std=c++14 -O0 -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer -nostartfiles -nodefaultlibs -ffreestanding -c -o $(POBJ)/$@ -c $<
ASM = g++-7
ASMFLAGS = $(CXXFLAGS)

include ../../Makefile.target
