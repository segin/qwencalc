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

# Source files for library
set(BACKEND_SOURCES
    ${CMAKE_SOURCE_DIR}/backend/CalculatorEngine.cpp
    ${CMAKE_SOURCE_DIR}/backend/ExpressionParser.cpp
    ${CMAKE_SOURCE_DIR}/backend/HistoryManager.cpp
    ${CMAKE_SOURCE_DIR}/frontend/ThemeManager.cpp
    ${CMAKE_SOURCE_DIR}/frontend/DisplayWidget.cpp
    ${CMAKE_SOURCE_DIR}/frontend/KeypadWidget.cpp
    ${CMAKE_SOURCE_DIR}/frontend/CalculatorWindow.cpp
)

# Library
add_library(qwencalc_lib STATIC ${BACKEND_SOURCES})
target_link_libraries(qwencalc_lib PRIVATE Qt6::Core Qt6::Widgets)

# Source files
set(TEST_SOURCES
    test_CalculatorEngine.cpp
    test_ExpressionParser.cpp
    test_HistoryManager.cpp
    test_integration.cpp
    test_frontend.cpp
)

# Test executable
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/backend
    ${CMAKE_SOURCE_DIR}/frontend
    ${CMAKE_SOURCE_DIR}/src
)

target_include_directories(qwencalc_lib PRIVATE
    ${CMAKE_SOURCE_DIR}/backend
    ${CMAKE_SOURCE_DIR}/frontend
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    gtest
    gtest_main
    qwencalc_lib
)

# Enable testing
enable_testing()
add_test(NAME qwencalc_tests COMMAND qwencalc_tests)

# Test configuration
if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
endif()
