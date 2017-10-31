
cmake_minimum_required(VERSION 2.6)

project (Neuron)
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(gtest)
include_directories(gtest/include gtest)

add_executable (Neuron Neuron.cpp Network.cpp main.cpp Constant.hpp)
add_executable (Neuron_unit_test1 Neuron.cpp Network.cpp Constant.hpp unitTest.cpp )

target_link_libraries (Neuron_unit_test1 gtest gtest_main)
add_test(Neuron_unit_test1 Neuron_unit_test1)




