#!/bin/bash

SCRIPT_NAME=`basename "$0"`
BINARY_FOLDER=bin
RESOURCE_BUILDER_BINARY=resource_builder
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

cmake --build $BUILD_DIR --target $RESOURCE_BUILDER_BINARY -j 2>&1

$BUILD_DIR/$BINARY_FOLDER/$RESOURCE_BUILDER_BINARY dev_battle_gui 2>&1
