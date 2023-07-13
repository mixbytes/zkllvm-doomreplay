cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(ZKLDoom)
include(CMakePrintHelpers)

list(APPEND CMAKE_MODULE_PATH 
    "/home/boogerwooger/zkllvm-doomreplay/cmake/"
    "${CMAKE_CURRENT_LIST_DIR}/cmake_modules/share/modules/cmake/"

)

include(CMConfig)
include(CMSetupVersion)
include(CircuitCompile)

# cmake_print_variables(CMAKE_MODULE_PATH)

cm_workspace(zkldoom)
cm_setup_version(VERSION 0.0.1 PREFIX ${CMAKE_WORKSPACE_NAME})

# macro(cm_find_package NAME)
#    if(NOT "${NAME}" MATCHES "^${CMAKE_WORKSPACE_NAME}_.*$" AND NOT "${NAME}" STREQUAL CM)
#        find_package(${ARGV})
#    else()
#        set(${ARGV0}_FOUND ON CACHE BOOL "")
#    endif()
# endmacro()


# add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/libs/crypto3")

#Directory with *.c and *.h doom sources
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/zkldoom")
