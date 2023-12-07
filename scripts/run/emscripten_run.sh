#!/bin/bash

SCRIPT_NAME=`basename "$0"`
BINARY_FOLDER=bin
echo "Processing $SCRIPT_NAME"

BUILD_DIR=build-em
EMSDK_DIR=workspace/emsdk

# TODO: clone emsdk as third_party via git submodule
source $HOME/$EMSDK_DIR/emsdk_env.sh

emrun $BUILD_DIR/$BINARY_FOLDER/dev_battle_gui.html