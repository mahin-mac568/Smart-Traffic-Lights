#!/bin/bash

mkdir -p Debug
cd Debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

cd bin
mkdir files
cd ..

cd ..
cp data/Traffic_Signals_SF.csv Debug/bin
