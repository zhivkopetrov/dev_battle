#!/bin/bash

SCRIPT_NAME=`basename "$0"`
echo "Processing $SCRIPT_NAME"

BUILD_DIR=build
ASSET_BUILD_DIR=$BUILD_DIR
ASSET_INSTALL_DIR=$ASSET_BUILD_DIR
CMAKE_BUILD_TYPE=Release

if [ -z "$1" ]; then
    echo "No argument supplied for CMAKE_BUILD_TYPE. Assuming '$CMAKE_BUILD_TYPE'"
    BUILD_DIR=build
else
    CMAKE_BUILD_TYPE=$1
    echo "Using CMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE"
fi

#build auto generated asset info
bash ./scripts/build/generate_asset_info.sh \
    $ASSET_BUILD_DIR $ASSET_INSTALL_DIR 2>&1

#install the generated asset info
cmake --install $ASSET_BUILD_DIR 2>&1

#do full configuration
cmake -S . -B $BUILD_DIR \
    -DCMAKE_INSTALL_PREFIX=$BUILD_DIR \
    -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE \
    -DASSET_BUILD=0 2>&1

#do full build
cmake --build $BUILD_DIR -j 2>&1