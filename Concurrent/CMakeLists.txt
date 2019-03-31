cmake_minimum_required (VERSION 3.8)

project (Concurrent CXX)
my_find_src_files (src_files Concurrent)
add_executable (Concurrent ${src_files})
my_add_compile_options (Concurrent)
my_add_pch (Concurrent)

my_inc_import_CCLib(Concurrent)
my_inc_import_RisLib(Concurrent)

my_lib_import_CCLib(Concurrent)
my_lib_import_RisLib(Concurrent)
