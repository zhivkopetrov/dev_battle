#!/bin/bash

SCRIPT_NAME=`basename "$0"`
echo "Processing $SCRIPT_NAME"

BUILD_DIR=build
ASSET_BUILD_DIR=$BUILD_DIR
ASSET_INSTALL_DIR=$ASSET_BUILD_DIR

#build auto generated asset info
bash ./scripts/build/generate_asset_info.sh \
    $ASSET_BUILD_DIR $ASSET_INSTALL_DIR 2>&1

#install the generated asset info
cmake --install $ASSET_BUILD_DIR 2>&1

#do full configuration
cmake -S . -B $BUILD_DIR \
    -DCMAKE_INSTALL_PREFIX=$BUILD_DIR \
    -DCMAKE_BUILD_TYPE=Debug \
    -DASSET_BUILD=0 2>&1

#do full build
cmake --build $BUILD_DIR -j 2>&1