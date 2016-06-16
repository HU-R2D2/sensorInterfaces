cmake_minimum_required(VERSION 2.8.9)
project(sensorinterfaces)
find_package (Threads)

file(GLOB SOURCES "source/src/*.cpp" "source/include/*.hpp")
file(GLOB SOURCES_GTEST "source/src/*.cpp" "source/include/*.hpp" "test/*.cpp" "test/*.hpp")
file(GLOB SOURCES_EXAMPLE_LIDAR "examples/VirtualLidarExample.cpp")
file(GLOB SOURCES_EXAMPLE_SONAR "examples/VirtualUltrasonicSensorExample.cpp")

file(GLOB INCLUDED_SOURCES "../polarview/source/src/*.cpp" "../adt/source/src/*.cpp" "../sharedobjects/source/src/*.cpp" "../map/source/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall")

include_directories(
  ../polarview/source/include
  ../adt/source/include
  ../sharedobjects/source/include
  ../map/source/include
  ../deps/hwlib
  ../deps/gtest-1.7.0/include
  ../deps/gtest-1.7.0)


link_directories(
  ../deps/gtest-1.7.0/src
  ../deps/hwlib
  ${INCLUDED_SOURCES})

ADD_LIBRARY(gtest ../deps/gtest-1.7.0/src/gtest-all.cc)
ADD_LIBRARY(gtest_main ../deps/gtest-1.7.0/src/gtest_main.cc)

add_executable(virtual_lidar_example ${SOURCES_EXAMPLE_LIDAR} ${SOURCES} ${INCLUDED_SOURCES})
add_executable(virtual_sonar_example ${SOURCES_EXAMPLE_SONAR} ${SOURCES} ${INCLUDED_SOURCES})
add_executable(sensor_test ${GTEST} ${SOURCES_GTEST} ${INCLUDED_SOURCES})

target_link_libraries(sensor_test gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
