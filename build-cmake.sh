#!/bin/bash

git submodule update

rm -rf ./out
mkdir ./out
cd ./out
cmake ..
