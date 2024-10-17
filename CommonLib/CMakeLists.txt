cmake_minimum_required(VERSION 3.10)
set (project "CommonLib")
project(${project} CXX)
my_find_src_files (src_files ${project})
add_library (${project} ${src_files})
my_add_pch (${project})

target_include_directories(CommonLib PUBLIC ${PROJECT_SOURCE_DIR})

my_inc_import_RisLib(CommonLib)

