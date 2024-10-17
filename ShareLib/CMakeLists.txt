cmake_minimum_required (VERSION 3.8)
set (project "ShareLib")
project(${project} CXX)

my_find_src_files (src_files ${project})
my_find_inc_files (inc_files)
add_library (${project} STATIC ${src_files})
my_add_compile_options (${project})
my_add_pch (${project})

target_include_directories(${project} PUBLIC ${PROJECT_SOURCE_DIR})

my_inc_import_CommonLib(${project})
my_inc_import_RisLib(${project})


