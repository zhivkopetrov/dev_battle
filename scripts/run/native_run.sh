#!/bin/bash

SCRIPT_NAME=`basename "$0"`
BINARY_FOLDER=bin
echo "Processing $SCRIPT_NAME"

BUILD_DIR=build

./$BUILD_DIR/$BINARY_FOLDER/dev_battle_gui 2>&1