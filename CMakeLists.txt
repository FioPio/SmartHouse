cmake_minimum_required(VERSION 3.12)
project(SmartHouse)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Find Opencv
#find_package(OpenCV REQUIRED)

# Include directories
#include_directories(include ${OpenCV_INCLUDE_DIRS})

find_library(CURL_LIBRARIES NAMES curl)


# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp)

target_link_libraries(SmartHouse PRIVATE ${CURL_LIBRARIES})

# Link against OpenCV
#target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

# Configure tests (if using Google Test)
#enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

# Add tests
#file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
#add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
#target_link_libraries(${PROJECT_NAME}_tests ${GTEST_BOTH_LIBRARIES})
#add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)

# Install executable
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Copy external dependencies (if needed)
# file(COPY externals/ DESTINATION ${CMAKE_BINARY_DIR}/externals/)
