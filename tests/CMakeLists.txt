cmake_minimum_required(VERSION 3.16)
project(qwencalc_tests)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    test_CalculatorEngine.cpp
    test_ExpressionParser.cpp
    test_HistoryManager.cpp
    test_integration.cpp
)

# Test executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/backend
    ${CMAKE_SOURCE_DIR}/frontend
    ${CMAKE_SOURCE_DIR}/src
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    gtest
    gtest_main
)

# Enable testing
enable_testing()

# Test configuration
if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
endif()
