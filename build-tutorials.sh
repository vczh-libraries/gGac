#!/bin/bash

git submodule update

function create-tutorial() {
    CATEGORY=$1
    APP=$2
    cd Tests
    if ! [ -d "$CATEGORY" ]; then
        mkdir $CATEGORY
    fi
    cd $CATEGORY
    if ! [ -d "$APP" ]; then
        mkdir $APP
    fi
    cd $APP
    echo "project($APP)" >> CMakeLists.txt
    echo "add_executable($APP" >> CMakeLists.txt
    echo "    ../../../GacUI/Tutorial/$CATEGORY/$APP/UI/Source/DemoPartialClasses.cpp" >> CMakeLists.txt
    echo "    ../../../GacUI/Tutorial/$CATEGORY/$APP/Main.cpp" >> CMakeLists.txt
    echo "    ../../App.cpp)" >> CMakeLists.txt
    echo "target_link_libraries ($APP \${FC_DEP_LIBS})" >> CMakeLists.txt
    cd ..
    cd ..
    cd ..
}

function create-tutorial-category() {
    CATEGORY=$1
    APPS=("${@:2}")
    for APP in "${APPS[@]}"; do
        APP_SOURCE="./GacUI/Tutorial/$CATEGORY/$APP"
        APP_DEST="./Tests/$CATEGORY/$APP"
        if [ -d "$APP_SOURCE" ]; then
            if ! [ -d "$APP_DEST" ]; then
                create-tutorial $CATEGORY $APP
            fi
            echo "ADD_SUBDIRECTORY(Tests/$CATEGORY/$APP)" >> build-tutorials.index.log
        else
            echo "$APP_SOURCE not found" >> build-tutorials.errors.log
        fi
    done
}

function build-tutorial() {
    CATEGORY=$1
    APP=$2
    cd "./$CATEGORY/$APP"
    make
    if ! [ -a "$APP" ]; then
        echo "$CATEGORY/$APP does not compile" >> ../../../../build-tutorials.errors.log
    fi
    cd ../..
}

function build-tutorial-category() {
    CATEGORY=$1
    APPS=("${@:2}")
    for APP in "${APPS[@]}"; do
        APP_DEST="./$CATEGORY/$APP"
        if [ -d "$APP_DEST" ]; then
            build-tutorial $CATEGORY $APP
        else
            echo "$APP_DEST not found" >> ../../build-tutorials.errors.log
        fi
    done
}

GACUI_HELLOWORLDS=(GacUI_HelloWorlds
    Cpp
    CppXml
    MVVM
    )
GACUI_LAYOUT=(GacUI_Layout
    Alignment
    Flow
    Responsive1
    Responsive2
    RichTextEmbedding
    SharedSize
    Stack
    Table
    TableSplitter
    )
GACUI_XML=(GacUI_Xml
    Binding_Bind
    Binding_Eval
    Binding_Format
    Binding_Uri
    Binding_ViewModel
    Event_Cpp
    Event_Script
    Event_ViewModel
    Instance_Control
    Instance_MultipleWindows
    Instance_Window
    Member_Field
    Member_Parameter
    Member_Property
    Misc_ImportFolder
    )
GACUI_CONTROLS=(GacUI_Controls
    AddressBook
    Animation
    CalculatorAndStateMachine
    ColorPicker
    ContainersAndButtons
    DataGrid
    DocumentEditorRibbon
    DocumentEditorToolstrip
    ListControls
    Localization
    MenuVisibility
    ProgressAndAsync
    QueryService
    TextEditor
    TriplePhaseImageButton
    )

if [ -a "build-tutorials.index.log" ]; then
    rm build-tutorials.index.log
fi
if [ -a "build-tutorials.errors.log" ]; then
    rm build-tutorials.errors.log
fi
create-tutorial-category "${GACUI_HELLOWORLDS[@]}"
create-tutorial-category "${GACUI_LAYOUT[@]}"
create-tutorial-category "${GACUI_XML[@]}"
create-tutorial-category "${GACUI_CONTROLS[@]}"
./build-cmake.sh
cd ./out
cmake ..
cd ./Tests
build-tutorial-category "${GACUI_HELLOWORLDS[@]}"
build-tutorial-category "${GACUI_LAYOUT[@]}"
build-tutorial-category "${GACUI_XML[@]}"
build-tutorial-category "${GACUI_CONTROLS[@]}"
cd ../..
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
if [ -a "build-tutorials.index.log" ]; then
    cat build-tutorials.index.log
    rm build-tutorials.index.log
fi
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
if [ -a "build-tutorials.errors.log" ]; then
    cat build-tutorials.errors.log
    rm build-tutorials.errors.log
fi
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"