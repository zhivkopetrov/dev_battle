#!/bin/bash

BUILD_DIR=build-em
EMSDK_DIR=workspace/emsdk

bash ./scripts/build/generate_asset_info.sh 2>&1

# TODO: clone emsdk as third_party via git submodule
source $HOME/$EMSDK_DIR/emsdk_env.sh

# install the generated asset info, because 
#emscripten `--preload-file`` needs it
cmake --install $BUILD_DIR 2>&1

emcmake cmake -S . -B $BUILD_DIR \
    -DCMAKE_INSTALL_PREFIX=$BUILD_DIR \
    -DCMAKE_BUILD_TYPE=Debug \
    -DASSET_BUILD=0 2>&1

cmake --build $BUILD_DIR -j 2>&1
#cmake --install $BUILD_DIR 2>&1