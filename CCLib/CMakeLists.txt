cmake_minimum_required (VERSION 3.8)

project (CCLib CXX)

my_find_src_files (src_files CCLib)
my_find_inc_files (inc_files)
if (MSVC)
   add_library (CCLib STATIC ${src_files})
else()
   add_library (CCLib SHARED ${src_files})
endif()
my_add_compile_options (CCLib)
my_add_pch (CCLib)

target_include_directories(CCLib PUBLIC ${PROJECT_SOURCE_DIR})

my_inc_import_RisLib(CCLib)

if (MSVC)
   install(FILES ${inc_files} DESTINATION "C:\\MyTools\\MyLib\\include\\CCLib")
   install(TARGETS CCLib DESTINATION "C:\\MyTools\\MyLib\\lib")
else()
   install(FILES ${inc_files} DESTINATION "/usr/local/include/CCLib")
   install(TARGETS CCLib DESTINATION "/usr/local/lib")
endif()
