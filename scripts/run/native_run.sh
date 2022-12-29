#!/bin/bash

SCRIPT_NAME=`basename "$0"`
echo "Processing $SCRIPT_NAME"

BUILD_DIR=build

./$BUILD_DIR/dev_battle_gui/dev_battle_gui 2>&1