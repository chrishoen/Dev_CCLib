cmake_minimum_required (VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(MY_MACRO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zzzMacros")
set(CMAKE_USER_MAKE_RULES_OVERRIDE "${MY_MACRO_DIR}/MyOverrides.cmake")
include("${MY_MACRO_DIR}/MyCodeMacros.cmake")
include("${MY_MACRO_DIR}/MyGlobalImports.cmake")
include("${MY_MACRO_DIR}/MyLocalImports.cmake")
include("${MY_MACRO_DIR}/MyPrecompiledHeader.cmake")
include("${MY_MACRO_DIR}/MySpecial.cmake")

project ("Dev_CCLib")
my_print_cmake_vars()


add_subdirectory ("CCLib")
add_subdirectory ("NDelay")
return()

add_subdirectory ("CCLib")
add_subdirectory ("RingShort")
return()

add_subdirectory ("CCLib")
add_subdirectory ("ShareLib")
add_subdirectory ("RingWriter")
add_subdirectory ("RingReader1")
add_subdirectory ("RingReader2")
return()

add_subdirectory ("Test")
return()

add_subdirectory ("CCLib")
add_subdirectory ("ShareLib")
add_subdirectory ("RingWriter")
add_subdirectory ("RingReader2")
return()

add_subdirectory ("Modulo")
return()

add_subdirectory ("CCLib")
add_subdirectory ("Concurrent")
add_subdirectory ("Test")
return()

add_subdirectory ("CCLib")
add_subdirectory ("ShareLib")
add_subdirectory ("RingWriter")
add_subdirectory ("RingReader")
return()

add_subdirectory ("CCLib")
add_subdirectory ("Concurrent")
add_subdirectory ("Test")
return()

add_subdirectory ("CCLib")
add_subdirectory ("Concurrent")
add_subdirectory ("LockFree")
add_subdirectory ("MyBlock")
add_subdirectory ("Test")


