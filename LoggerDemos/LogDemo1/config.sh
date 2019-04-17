#!/bin/sh

mkdir build
cd build

cmake ../
make

cp demo ../
cd ../

