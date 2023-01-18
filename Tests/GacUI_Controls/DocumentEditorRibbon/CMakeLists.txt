project(DocumentEditorRibbon)
add_executable(DocumentEditorRibbon
		../../../GacUI/Tutorial/GacUI_Controls/DocumentEditor/UI/Source/DocumentEditorBase.cpp
		../../../GacUI/Tutorial/GacUI_Controls/DocumentEditor/UI/Source/EditorBasePartialClasses.cpp
		../../../GacUI/Tutorial/GacUI_Controls/DocumentEditorRibbon/UI/Source/EditorRibbonPartialClasses.cpp
		../../../GacUI/Tutorial/GacUI_Controls/DocumentEditorRibbon/Main.cpp
		../../App.cpp)
include_directories(../../../GacUI/Tutorial/GacUI_Controls/DocumentEditor/UI/Source)
target_link_libraries (DocumentEditorRibbon ${gGac_LIBRARIES})