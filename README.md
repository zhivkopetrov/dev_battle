# dev_battle
# run project from the build folder

cmake .. -DCMAKE_INSTALL_PREFIX=$PWD
make resource_builder -j
./res_builder dev_battle_gui
make -j
cmake --install .
./gui 