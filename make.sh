#!/bin/sh
cd build
cmake ..
make

cp -rf ../data ./