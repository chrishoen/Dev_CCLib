﻿cmake_minimum_required(VERSION 3.10)
set (project "Delete")
project(${project} CXX)
my_find_src_files (src_files ${project})
add_executable (${project} ${src_files})
my_add_compile_options (${project})
my_add_pch (${project})

my_inc_import_CCLib(${project})
my_inc_import_RisLib(${project})

my_lib_import_CCLib(${project})
my_lib_import_RisLib(${project})

if (MSVC)
   install(TARGETS ${project} DESTINATION "C:/aaa_prime/CCLib")
elseif (MYMODE MATCHES "cpdev1" OR MYMODE MATCHES "wsl") 
   install(TARGETS ${project} DESTINATION "/opt/prime/bin")
elseif (MYMODE MATCHES "beagle")
   install(CODE "execute_process(COMMAND_ECHO STDOUT
      COMMAND c:/windows/system32/openssh/scp ${CMAKE_CURRENT_BINARY_DIR}/${project} pi@rpx:/opt/prime/bin)")
endif()
