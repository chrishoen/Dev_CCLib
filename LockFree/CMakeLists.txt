cmake_minimum_required (VERSION 3.8)

project (LockFree CXX)
my_find_src_files (src_files LockFree)
add_executable (LockFree ${src_files})
my_add_compile_options (LockFree)
my_add_pch (LockFree)

my_inc_import_CCLib(LockFree)
my_inc_import_RisLib(LockFree)

my_lib_import_CCLib(LockFree)
my_lib_import_RisLib(LockFree)
