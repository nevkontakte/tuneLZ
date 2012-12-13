cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

#---------------------- Project setup -----------------------------

set(PROJECT_NAME tuneLZ)
project(${PROJECT_NAME} CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

#---------------------- Enable C++11 support ----------------------

if(CMAKE_COMPILER_IS_GNUCXX)
   execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
        message(STATUS "C++11 activated.")
        add_definitions("-std=gnu++11")
   elseif(GCC_VERSION VERSION_GREATER 4.3 OR GCC_VERSION VERSION_EQUAL 4.3)
        message(WARNING "C++0x activated. If you get any errors update to a compiler which fully supports C++11")
        add_definitions("-std=gnu++0x")
   else ()
        message(FATAL_ERROR "C++11 needed. Therefore a gcc compiler with a version higher than 4.3 is needed.")   
   endif()
else(CMAKE_COMPILER_IS_GNUCXX)
   add_definitions("-std=c++0x") 
endif(CMAKE_COMPILER_IS_GNUCXX)

#---------------------- Building main binary ----------------------

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cc)
source_group("Source Files" FILES ${SRC_FILES})

# Uncomment later, when main binary will be available
add_executable(${PROJECT_NAME}_unlim ${SRC_FILES} runnable/tuneLZ_unlim.cc) 
add_executable(${PROJECT_NAME}_len ${SRC_FILES} runnable/tuneLZ_len.cc) 
add_executable(${PROJECT_NAME}_size ${SRC_FILES} runnable/tuneLZ_size.cc) 

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