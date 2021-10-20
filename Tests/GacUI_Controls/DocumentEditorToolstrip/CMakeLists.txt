project(DocumentEditorToolstrip)
add_executable(DocumentEditorToolstrip
    ../../../GacUI/Tutorial/GacUI_Controls/DocumentEditorToolstrip/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/DocumentEditorToolstrip/Main.cpp
    ../../App.cpp)
target_link_libraries (DocumentEditorToolstrip ${FC_DEP_LIBS})
