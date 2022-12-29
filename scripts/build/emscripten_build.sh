#!/bin/bash

SCRIPT_NAME=`basename "$0"`
echo "Processing $SCRIPT_NAME"

BUILD_DIR=build-em
ASSET_BUILD_DIR=build
ASSET_INSTALL_DIR=$BUILD_DIR
EMSDK_DIR=workspace/emsdk

#build auto generated asset info
bash ./scripts/build/generate_asset_info.sh \
    $ASSET_BUILD_DIR $ASSET_INSTALL_DIR 2>&1

#install auto generated asset info, because 
#emscripten `--preload-file`` needs it
cmake --install $ASSET_BUILD_DIR 2>&1

# TODO: clone emsdk as third_party via git submodule
#load the emscripten toolchain
source $HOME/$EMSDK_DIR/emsdk_env.sh

#do full configuration
emcmake cmake -S . -B $BUILD_DIR \
    -DCMAKE_INSTALL_PREFIX=$BUILD_DIR \
    -DCMAKE_BUILD_TYPE=Debug \
    -DASSET_BUILD=0 2>&1

#do full build
cmake --build $BUILD_DIR -j 2>&1
