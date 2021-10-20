project(DocumentEditorToolstrip)
add_executable(DocumentEditorToolstrip
    ../../../GacUI/Tutorial/GacUI_Controls/DocumentEditor/UI/Source/DocumentEditorBase.cpp
	../../../GacUI/Tutorial/GacUI_Controls/DocumentEditor/UI/Source/EditorBasePartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/DocumentEditorToolstrip/UI/Source/EditorToolstripPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/DocumentEditorToolstrip/Main.cpp
    ../../App.cpp)
include_directories(../../../GacUI/Tutorial/GacUI_Controls/DocumentEditor/UI/Source)
target_link_libraries (DocumentEditorToolstrip ${FC_DEP_LIBS})
