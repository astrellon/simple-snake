#!/bin/sh
mkdir -p debug
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j4

cp -rf ../data ./
