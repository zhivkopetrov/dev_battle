#!/bin/bash

BUILD_DIR=build

cmake -S . -B build \
    -DCMAKE_INSTALL_PREFIX=$BUILD_DIR \
    -DCMAKE_BUILD_TYPE=Debug \
    -DASSET_BUILD=1 2>&1

cmake --build $BUILD_DIR --target resource_builder -j 2>&1

$BUILD_DIR/tools/resource_builder/resource_builder dev_battle_gui 2>&1