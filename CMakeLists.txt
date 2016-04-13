cmake_minimum_required(VERSION 2.6)

set(MSGPACK_BUILD_TESTS OFF CACHE BOOL "Build msgpack tests")
set(MSGPACK_BUILD_EXAMPLES OFF CACHE BOOL "Build msgpack examples")

add_subdirectory(contrib/msgpack-c)
add_subdirectory(contrib/benchmark)

project(roidcore)
list(APPEND msgpack_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/contrib/msgpack-c/include")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/contrib/wubwubcmake/modules")

include("contrib/wubwubcmake/enable_cpp14.cmake")
include("contrib/wubwubcmake/warning_settings.cmake")
add_sane_warning_flags()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g -fno-exceptions -fno-rtti -fno-omit-frame-pointer")

list(APPEND roidcore_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/src/")
list(APPEND roidcore_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/contrib/glm/")
list(APPEND roidcore_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/contrib/benchmark/include/")

add_subdirectory("src/roidcore")
