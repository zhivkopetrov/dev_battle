# dev_battle

**A C++ placeholder project for a future 2D GUI game**

The project uses plain CMake.

**Git submodules**
This repository has it's dependencies configured as git submodules.
To clone them, step inside the repository and run the following instructions
```
git submodule init
git submodule update
```


**CMake configuration**
```
# step inside the 'build' folder

# configure the project
cmake .. -DCMAKE_INSTALL_PREFIX=$PWD

# You can specify the project type or a different compiler
# For example:
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$PWD -DCMAKE_CXX_COMPILER=/usr/bin/clang++
```


**Automatic asset information generation**
The first time the project is build it will fail compilation, because you are missing some auto-generated headers.
This step should be executed only once in the beginning.
Or everytime you modify some of the resource files (asset information descriptions)

To resolve this follow the instructios:
```
# step inside the 'build' folder

# build the resource builder tool
make resource_builder -j

# auto generate C++ headers and asset information for the GUI project:
./tools/resource_builder/resource_builder dev_battle_gui
```


**Building the project**
Once the resource_builder has generated asset_information you can build the project normally
```
#step inside the 'build' folder

# build the whole project
make -j

# install the build artifacts
cmake --install .
```


**Running the project**
```
./dev_battle_gui/dev_battle_gui
```


**Dependency hierarchy diagram**
![](doc/dev_battle_gui_hierarchy_diagram.svg)
