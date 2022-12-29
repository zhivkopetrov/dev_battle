#!/bin/bash

SCRIPT_NAME=`basename "$0"`
echo "Processing $SCRIPT_NAME"

if [ -z "$1" ]; then
    echo "No argument supplied for BUILD_DIR. Assuming 'build'"
    BUILD_DIR=build
else
    BUILD_DIR=$1
    echo "Using BUILD_DIR=$BUILD_DIR"
fi

if [ -z "$2" ]; then
    echo "No argument supplied for ASSET_INSTALL_DIR. Assuming '$BUILD_DIR'"
    ASSET_INSTALL_DIR=$BUILD_DIR
else
    ASSET_INSTALL_DIR=$2
    echo "Using ASSET_INSTALL_DIR=$ASSET_INSTALL_DIR"
fi

cmake -S . -B $BUILD_DIR \
    -DCMAKE_INSTALL_PREFIX=$ASSET_INSTALL_DIR \
    -DCMAKE_BUILD_TYPE=Debug \
    -DASSET_BUILD=1 2>&1

cmake --build $BUILD_DIR --target resource_builder -j 2>&1

$BUILD_DIR/tools/resource_builder/resource_builder dev_battle_gui 2>&1
