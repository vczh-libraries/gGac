#!/bin/bash

git submodule update

rm -rf ./out
mkdir ./out
cd ./out
cmake ..

pushd ./Tests/GacUI_HelloWorlds
ln -s ../../../GacUI/Tutorial/GacUI_HelloWorlds/UIRes UIRes
popd

pushd ./Tests/GacUI_Controls
ln -s ../../../GacUI/Tutorial/GacUI_Controls/UIRes UIRes
popd

pushd ./Tests/GacUI_Layout
ln -s ../../../GacUI/Tutorial/GacUI_Layout/UIRes UIRes
popd