#!/bin/sh -x
mkdir -p build
cd build
cmake -DBUILD_TESTS=ON -GNinja ..
ninja 
