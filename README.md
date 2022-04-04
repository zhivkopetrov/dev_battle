# dev_battle
# run project from the build folder

cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$PWD -DCMAKE_CXX_COMPILER=/usr/bin/clang++
make resource_builder -j
./tools/resource_builder/resource_builder dev_battle_gui
make -j
cmake --install .
./gui 