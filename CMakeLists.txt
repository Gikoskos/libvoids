cmake_minimum_required(VERSION 2.8.12)

project(libvoids)

enable_testing()


option(BUILD_SHARED_LIBS "Build shared libs" OFF)

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

add_subdirectory(lib)
add_subdirectory(tests)
