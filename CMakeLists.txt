cmake_minimum_required(VERSION 2.8.9)
project(sharedInterfaces)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Wno-comment -Wno-missing-field-initializers -fpermissive")

file(GLOB SOURCES "source/include/*.hpp" "source/src/*.cpp")
file(GLOB SOURCES_GTEST "source/include/*.hpp" "test/*.cpp" "test/*.hpp")
list(REMOVE_ITEM SOURCES_GTEST ${CMAKE_CURRENT_SOURCE_DIR}/source/src/UltrasonicSensorTestCode.cpp)

include_directories(
  ../deps/gtest-1.7.0/include
  ../deps/gtest-1.7.0
  ../deps/hwlib
  ../deps/adt/source/include
  ../deps/polarview/source/include
  )

link_directories(
  ../deps/gtest-1.7.0/src
  ../deps/hwlib
  ../deps/adt/source/src
  ../deps/polarview/source/src)

ADD_LIBRARY(gtest ../deps/gtest-1.7.0/src/gtest-all.cc)
ADD_LIBRARY(gtest_main ../deps/gtest-1.7.0/src/gtest_main.cc)
ADD_LIBRARY(hwlib "../deps/hwlib/hwlib.c")
ADD_LIBRARY(adt "../deps/adt/source/adt-all.cc")
ADD_LIBRARY(polarview "../deps/polarview/source/polarview-all.cc")

add_executable(sensorInterfaces ${SOURCES})
add_executable(sensorInterfaces_test ${GTEST} ${SOURCES_GTEST})

target_link_libraries(sensorInterfaces hwlib adt polarview)
target_link_libraries(sensorInterfaces_test hwlib adt polarview gtest gtest_main)
