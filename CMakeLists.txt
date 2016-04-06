cmake_minimum_required(VERSION 2.8.9)
project(sharedInterfaces)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Wno-comment -Wno-missing-field-initializers -Werror -pedantic")

file(GLOB SOURCES "source/include/*.hpp" "source/src/*.cpp")
file(GLOB SOURCES_GTEST "source/include/*.hpp" "test/*.cpp" "test/*.hpp")

include_directories(
  ../deps/gtest-1.7.0/include
  ../deps/gtest-1.7.0)

link_directories(../deps/gtest-1.7.0/src)
ADD_LIBRARY(gtest ../deps/gtest-1.7.0/src/gtest-all.cc)
ADD_LIBRARY(gtest_main ../deps/gtest-1.7.0/src/gtest_main.cc)

add_executable(sensorInterfaces_test ${GTEST} ${SOURCES_GTEST})
target_link_libraries(sensorInterfaces_test gtest gtest_main)
