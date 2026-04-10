cmake_minimum_required(VERSION 3.16)
project(qwencalc VERSION 0.1.0 LANGUAGES C++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Qt6 configuration
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

qt_standard_project_setup()

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/backend
    ${CMAKE_SOURCE_DIR}/frontend
)

# Source files
set(SOURCES
    src/main.cpp
    backend/CalculatorEngine.cpp
    backend/ExpressionParser.cpp
    backend/HistoryManager.cpp
    frontend/CalculatorWindow.cpp
    frontend/DisplayWidget.cpp
    frontend/KeypadWidget.cpp
    frontend/ThemeManager.cpp
)

# Header files
set(HEADERS
    backend/CalculatorEngine.h
    backend/ExpressionParser.h
    backend/HistoryManager.h
    frontend/CalculatorWindow.h
    frontend/DisplayWidget.h
    frontend/KeypadWidget.h
    frontend/ThemeManager.h
)

# Executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# No .ui files used - all UI is built programmatically

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
)

# Install target
install(TARGETS ${PROJECT_NAME} BUNDLE DESTINATION .)

# Build type configuration
if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
endif()

# Test configuration
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
