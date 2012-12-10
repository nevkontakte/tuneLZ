cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

#---------------------- Project setup -----------------------------

set(PROJECT_NAME tuneLZ)
project(${PROJECT_NAME} CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

#---------------------- Building main binary ----------------------

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cc)
source_group("Source Files" FILES ${SRC_FILES})

# Uncomment later, when main binary will be available
add_executable(${PROJECT_NAME}_unlim ${SRC_FILES} runnable/tuneLZ_unlim.cc) 
add_executable(${PROJECT_NAME}_size64 ${SRC_FILES} runnable/tuneLZ_size64.cc) 
add_executable(${PROJECT_NAME}_size128 ${SRC_FILES} runnable/tuneLZ_size128.cc) 
add_executable(${PROJECT_NAME}_size256 ${SRC_FILES} runnable/tuneLZ_size256.cc) 
add_executable(${PROJECT_NAME}_size512 ${SRC_FILES} runnable/tuneLZ_size512.cc) 
add_executable(${PROJECT_NAME}_size1024 ${SRC_FILES} runnable/tuneLZ_size1024.cc) 

#---------------------- Building unit tests ------------------------

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_BINARY ${PROJECT_NAME}_test)

file(GLOB TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.cc)
source_group("Test Files" FILES ${SRC_FILES})

add_executable(${TEST_BINARY} ${TEST_FILES} ${SRC_FILES})
target_link_libraries(${TEST_BINARY}  ${GTEST_BOTH_LIBRARIES})
target_link_libraries(${TEST_BINARY}  pthread)

#---------------------- Set up CTest -------------------------------

enable_testing()
add_test(TestBinary ${TEST_BINARY})
GTEST_ADD_TESTS(${TEST_BINARY} "" ${TEST_FILES})