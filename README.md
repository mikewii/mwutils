 
### Build and install:
```sh
mkdir build
cd build
cmake ..
make
sudo make install
```
project configured to build both static and shared libs at same time


### Usage:
#### As interface:
clone repository to your project external libs folder and link it
```cmake
add_subdirectory(<EXT_LIBS_DIR>/mwutils)
target_link_libraries(${PROJECT_NAME} PRIVATE mwutils::mwutils)
```

#### As static:
```cmake
target_link_libraries(${PROJECT_NAME} PRIVATE mwutils.a)
```

#### As shared:
```cmake
target_link_libraries(${PROJECT_NAME} PRIVATE mwutils)
```
