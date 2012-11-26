cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

#---------------------- Project setup -----------------------------

set(PROJECT_NAME tuneLZ)
project(${PROJECT_NAME} C)

#---------------------- Building main binary ----------------------

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
source_group("Source Files" FILES ${SRC_FILES})

# Uncomment later, when main binary will be available
# add_executable(${PROJECT_NAME} ${SRC_FILES}) 

#---------------------- Building unit tests ------------------------

set(TEST_BINARY ${PROJECT_NAME}_test)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/CuTest)
include_directories(${PROJECT_SOURCE_DIR}/lib/CuTest)

file(GLOB TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.c)
source_group("Test Files" FILES ${SRC_FILES})

add_executable(${TEST_BINARY} ${TEST_FILES} ${SRC_FILES})
target_link_libraries(${TEST_BINARY} CuTest)

#---------------------- Set up CTest -------------------------------

enable_testing()
add_test(CuTest ${TEST_BINARY})