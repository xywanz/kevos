# /* Copyright 2017 Shoukai Liu (http://github.com/stormycatcat/). All Rights Reserved.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#     http://www.apache.org/licenses/LICENSE-2.0
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================*/

POBJ = ../build

LD = ld
LDFLAG = -z max-page-size=0x1000 -T $(POBJ)/lds/x64/kernel-ld-script.ld

OBJ := $(wildcard $(POBJ)/*.o)

kernel.bin:
	$(LD) $(LDFLAG) $(OBJ)

all:
	make -C lib/src/
	make -C lib/src/stdlib/
	make -C lib/src/string/
	make -C lib/src/stdio/
	make -C x86/
	make -C kernel/
	make

.PHONY:clean
clean:
	rm -rf $(OBJ) $(POBJ)/kernel.bin