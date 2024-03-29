﻿cmake_minimum_required (VERSION 3.8)
set (project "ShareLib")
project(${project} CXX)

my_find_src_files (src_files ${project})
my_find_inc_files (inc_files)
add_library (${project} STATIC ${src_files})
my_add_compile_options (${project})
my_add_pch (${project})

target_include_directories(${project} PUBLIC ${PROJECT_SOURCE_DIR})

my_inc_import_CCLib(${project})
my_inc_import_RisLib(${project})

return()

if (MSVC)
   install(FILES ${inc_files} DESTINATION "C:/MyTools/MyLib/include/ShareLib")
   install(TARGETS ${project} DESTINATION "C:/MyTools/MyLib/lib")
elseif(MYMODE STREQUAL "cpdev1" OR MYMODE STREQUAL "wsl")
   install(FILES ${inc_files} DESTINATION "/opt/prime/include/ShareLib")
   install(TARGETS ${project} DESTINATION "/opt/prime/lib")
elseif(MYMODE STREQUAL "beagle")
   install(FILES ${inc_files} DESTINATION "C:/MyTools/MyLib/include/ShareLib")
   install(TARGETS ${project} DESTINATION "C:/MyTools/MyLib/lib")
elseif(MYMODE STREQUAL "steno-arm")
   install(FILES ${inc_files} DESTINATION "include/ShareLib")
   install(TARGETS ${project} DESTINATION "lib/arm")
elseif(MYMODE STREQUAL "steno-wsl")
   install(FILES ${inc_files} DESTINATION "include/ShareLib")
   install(TARGETS ShareLib DESTINATION "lib/x86")
endif()

