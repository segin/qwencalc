cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

project(qwencalc LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt6_add_resources(qwencalc_resources)

add_executable(qwencalc
    src/main.cpp
    backend/CalculatorEngine.cpp
    backend/ExpressionParser.cpp
    backend/HistoryManager.cpp
    frontend/CalculatorWindow.cpp
    frontend/DisplayWidget.cpp
    frontend/KeypadWidget.cpp
    frontend/ThemeManager.cpp
)

target_include_directories(qwencalc PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/backend
    ${CMAKE_SOURCE_DIR}/frontend
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(qwencalc PRIVATE
    Qt6::Core
    Qt6::Widgets
)

target_compile_options(qwencalc PRIVATE
    -Wall
    -Wextra
    -Werror
)

install(TARGETS qwencalc BUNDLE DESTINATION .)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
