#!/bin/bash

BUILD_DIR=build

bash ./scripts/build/generate_asset_info.sh 2>&1

cmake -S . -B $BUILD_DIR \
    -DCMAKE_INSTALL_PREFIX=$BUILD_DIR \
    -DCMAKE_BUILD_TYPE=Debug \
    -DASSET_BUILD=0 2>&1

cmake --build $BUILD_DIR -j 2>&1
cmake --install $BUILD_DIR 2>&1