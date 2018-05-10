
add_subdirectory(arch)
add_subdirectory(kernel)

include(arch/${ARCH}/CMakeLists.subdir)