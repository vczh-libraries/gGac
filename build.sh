#!/bin/bash

git submodule update

rm -rf ./out
mkdir ./out
cd ./out
cmake ..

if [ -d "Tests" ]; then
    cd Tests
    GACUI_FOLDERS=(GacUI_HelloWorlds GacUI_Layout GacUI_Xml GacUI_Controls GacUI_ControlTemplate)
    for i in "${GACUI_FOLDERS[@]}"; do
        if ! [ -d "$i" ]; then
            mkdir "$i"
        fi
        cd "$i"
        ln -s "../../../GacUI/Tutorial/$i/UIRes" UIRes
        cd ..
    done
    cd ..
fi