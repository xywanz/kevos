cmake_minimum_required(VERSION 3.0)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
project(kevos)

if("${INC}" STREQUAL "")
	set(INC include)
endif("${INC}" STREQUAL "")

if("${ARCH}" STREQUAL "")
	set(ARCH x64)
endif("${ARCH}" STREQUAL "")

if("${SCRIPTS}" STREQUAL "")
	set(SCRIPTS ${CMAKE_BINARY_DIR}/..)
endif("${SCRIPTS}" STREQUAL "")

include(src/arch/${ARCH}/CMakeLists.compiler)

include_directories(${INC})

add_subdirectory(src)

execute_process(COMMAND ${LD_EXECUTABLE} ${LD_ARGUMENTS})

set(CXX_NOFLAGS ${CXX_NOFLAGS} -fno-builtin -nostdinc -nostdinc++ -nostdlib)
set(CXX_NOFLAGS ${CXX_NOFLAGS} -fno-rtti -fno-exceptions -fno-PIC -fno-stack-protector)
set(CXX_NOFLAGS ${CXX_NOFLAGS} -mno-mmx -mno-sse2 -mno-sse3 -mno-3dnow -momit-leaf-frame-pointer)
set(CXX_NOFLAGS ${CXX_NOFLAGS} -nostartfiles -nodefaultlibs -ffreestanding)

set(LD_ARGUMENTS ${LD_ARGUMENTS} -Wl,-T ${CMAKE_SOURCE_DIR}/src/arch/${ARCH}/kernel-ld-script.ld)
set(LD_ARGUMENTS ${LD_ARGUMENTS} ${CXX_NOFLAGS})
set(LD_ARGUMENTS ${LD_ARGUMENT} -Wl,--start-group)
foreach(module_name ${MODULE_LIST})
	set(LD_ARGUMENTS ${LD_ARGUMENTS} -o ${CMAKE_BINARY_DIR}/${module_name}.a)
endforeach(module_name ${MODULE_LIST})
set(LD_ARGUMENTS ${LD_ARGUMENTS} -Wl,--end-group)


add_custom_command(OUTPUT kernel_img
	COMMENT "Copy kernel.bin to vd.vmdk"
	COMMAND ${SCRIPTS}/write_vmdk.sh
	WORKING_DIRECTORY ${SCRIPTS})