#!/bin/bash

function create-tutorial() {
    CATEGORY=$1
    APPS=("${@:2}")
    echo $CATEGORY
    for APP in "${APPS[@]}"; do
        APP_SOURCE="./GacUI/Tutorial/$CATEGORY/$APP"
        APP_DEST="./Tests/$CATEGORY/$APP"
        if [ -d "$APP_SOURCE" ]; then
            if ! [ -d "$APP_DEST" ]; then
                echo "    $APP"
            else
                echo "$APP_DEST found" >> build-tutorials.log
            fi
        else
            echo "$APP_SOURCE not found" >> build-tutorials.log
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

if [ -a "build-tutorials.log" ]; then
    rm build-tutorials.log
fi
create-tutorial "${GACUI_HELLOWORLDS[@]}"
create-tutorial "${GACUI_LAYOUT[@]}"
create-tutorial "${GACUI_XML[@]}"
create-tutorial "${GACUI_CONTROLS[@]}"