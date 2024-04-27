project(DocumentEditorToolstrip)
add_executable(DocumentEditorToolstrip
    ../../../Release/Tutorial/GacUI_Controls/DocumentEditor/UI/Source/DocumentEditorBase.cpp
	../../../Release/Tutorial/GacUI_Controls/DocumentEditor/UI/Source/EditorBasePartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Controls/DocumentEditorToolstrip/UI/Source/EditorToolstripPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Controls/DocumentEditorToolstrip/Main.cpp
    ../../App.cpp)
include_directories(../../../Release/Tutorial/GacUI_Controls/DocumentEditor/UI/Source)
target_link_libraries (DocumentEditorToolstrip ${gGac_LIBRARIES})
