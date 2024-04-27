project(DocumentEditorRibbon)
add_executable(DocumentEditorRibbon
		../../../Release/Tutorial/GacUI_Controls/DocumentEditor/UI/Source/DocumentEditorBase.cpp
		../../../Release/Tutorial/GacUI_Controls/DocumentEditor/UI/Source/EditorBasePartialClasses.cpp
		../../../Release/Tutorial/GacUI_Controls/DocumentEditorRibbon/UI/Source/EditorRibbonPartialClasses.cpp
		../../../Release/Tutorial/GacUI_Controls/DocumentEditorRibbon/Main.cpp
		../../App.cpp)
include_directories(../../../Release/Tutorial/GacUI_Controls/DocumentEditor/UI/Source)
target_link_libraries (DocumentEditorRibbon ${gGac_LIBRARIES})