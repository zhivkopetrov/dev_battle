#!/bin/bash

BUILD_DIR=build-em
EMSDK_DIR=workspace/emsdk

# TODO: clone emsdk as third_party via git submodule
source $HOME/$EMSDK_DIR/emsdk_env.sh

emrun $BUILD_DIR/dev_battle_gui/dev_battle_gui.html