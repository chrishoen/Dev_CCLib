cmake_minimum_required (VERSION 3.8)

project (MyBlock CXX)
my_find_src_files (src_files MyBlock)
add_executable (MyBlock ${src_files})
my_add_compile_options (MyBlock)
my_add_pch (MyBlock)

my_inc_import_CCLib(MyBlock)
my_inc_import_RisLib(MyBlock)

my_lib_import_CCLib(MyBlock)
my_lib_import_RisLib(MyBlock)
