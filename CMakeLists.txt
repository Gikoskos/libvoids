cmake_minimum_required(VERSION 2.8.12)

project(EduDS)

enable_testing()

#set(BUILD_SHARED_LIBS ON)
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

add_subdirectory(lib)
add_subdirectory(tests)
