#!/bin/sh
mkdir -p build
cd build
cmake ..
make

cp -rf ../data ./
