﻿cmake_minimum_required(VERSION 3.10)
if (MSVC)
   return()
endif()
set (project "RingWriter")
project(${project} CXX)
my_find_src_files (src_files ${project})
add_executable (${project} ${src_files})
my_add_compile_options (${project})
my_add_pch (${project})

my_inc_import_RisLib(${project})
my_inc_import_CCLib(${project})
my_inc_import_RingLib(${project})

my_lib_import_RingLib(${project})
my_lib_import_CCLib(${project})
my_lib_import_RisLib(${project})


include("${MY_MACRO_DIR}/MyInstall.cmake")
