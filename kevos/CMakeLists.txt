
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(kevos)

SET(LIB_PATH "${PROJECT_SOURCE_DIR}/src/user/lib")

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES("${LIB_PATH}/stdlib/include/stdinc")
INCLUDE_DIRECTORIES("${LIB_PATH}/stdlib/include/stdinc++")
INCLUDE_DIRECTORIES("${LIB_PATH}/stl/include")

SET(C_FLAGS "${C_FLAGS} -std=c11 -m64 -O0 -c")
SET(C_FLAGS "${C_FLAGS} -nodefaultlibs -nostdinc -nostdlib -fno-builtin")
SET(C_FLAGS "${C_FLAGS} -momit-leaf-frame-pointer")
SET(C_FLAGS "${C_FLAGS} -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow")
SET(C_FLAGS "${C_FLAGS} -fno-exceptions -fno-PIC -fno-stack-protector -nostartfiles -ffreestanding")
SET(C_FLAGS "${C_FLAGS} -mcmodel=kernel")

SET(CXX_FLAGS "${CXX_FLAGS} -std=c++14 -m64 -O0 -c")
SET(CXX_FLAGS "${CXX_FLAGS} -nodefaultlibs -nostdinc -nostdlib -fno-builtin")
SET(CXX_FLAGS "${CXX_FLAGS} -momit-leaf-frame-pointer")
SET(CXX_FLAGS "${CXX_FLAGS} -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow")
SET(CXX_FLAGS "${CXX_FLAGS} -fno-exceptions -fno-PIC -fno-stack-protector -nostartfiles -ffreestanding")
SET(CXX_FLAGS "${CXX_FLAGS} -mcmodel=kernel")

SET(ASM_FLAGS "${CXX_FLAGS}")