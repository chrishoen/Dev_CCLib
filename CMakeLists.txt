cmake_minimum_required (VERSION 3.8)

include(MyPrecompiledHeader.cmake)
include(MyCodeMacros.cmake)
include(MyLocalImports.cmake)
include(MyGlobalImports.cmake)

project ("Dev_CCLib")
my_init_global_import_variables()

add_subdirectory ("CCLib")
add_subdirectory ("Concurrent")
add_subdirectory ("LockFree")
add_subdirectory ("MyBlock")
add_subdirectory ("Test")


