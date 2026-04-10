#!/bin/bash

# QwenCalc Build Script

set -e

echo "Building QwenCalc..."

# Get Qt6 installation path
QT_PATH=$(qt6-cmake-config-path Qt6 2>/dev/null || echo "/usr/lib/x86_64-linux-gnu/cmake/Qt6")

# Configure CMake
cmake -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_PREFIX_PATH="$QT_PATH"

# Build
cmake --build build -j$(nproc)

# Run tests
cd build
ctest --output-on-failure

echo "Build complete!"
echo "Executable: ./qwencalc"
echo "Tests: ./tests/qwencalc_tests"
