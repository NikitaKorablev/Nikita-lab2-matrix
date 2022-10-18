cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(Matrix)

include(function.cmake)
option(BTEST "build test?" ON)

add_subdirectory(samples)

if(BTEST)
    add_subdirectory(gtest)
    add_subdirectory(test)
endif()
unset(BTEST CACHE)