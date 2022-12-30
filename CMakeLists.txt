project(gGac)
cmake_minimum_required(VERSION 3.17)
add_compile_definitions(VCZH_DEBUG_NO_REFLECTION)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtkmm-3.0 sigc++-2.0)
pkg_check_modules(pango REQUIRED pango)

add_library(GacUI
        GacUI/Import/GacUI.cpp
        GacUI/Import/Vlpp.cpp
        GacUI/Import/Vlpp.Linux.cpp
        GacUI/Import/VlppOS.cpp
        GacUI/Import/VlppOS.Linux.cpp
        GacUI/Import/VlppRegex.cpp
        GacUI/Import/VlppReflection.cpp
        GacUI/Import/VlppParser.cpp
		GacUI/Import/VlppGlrParser.cpp
		GacUI/Import/VlppWorkflowLibrary.cpp
        GacUI/Import/Skins/DarkSkin/DarkSkin.cpp
        )

add_library(gGac
        Source/Services/GGacCallbackService.cpp
        Source/Services/GGacInputService.cpp
        Source/Services/GGacAsyncService.cpp
        Source/Services/GGacImageService.cpp
        Source/Services/GGacDialogService.cpp
        Source/Services/GGacResourceService.cpp
        Source/Services/GGacScreenService.cpp
        Source/Services/GGacClipboardService.cpp
        Source/Renderers/GuiSolidBorderElementRenderer.cpp
        Source/Renderers/GGacRenderer.cpp
        Source/Renderers/Gui3DBorderElementRenderer.cpp
        Source/Renderers/GuiSoldBackgroundElementRenderer.cpp
        Source/Renderers/GuiSolidLabelElementRenderer.cpp
        Source/Renderers/Gui3DSplitterElementRenderer.cpp
        Source/Renderers/GuiGradientBackgroundElementRenderer.cpp
        Source/Renderers/GuiImageFrameElementRenderer.cpp
        Source/Renderers/GuiPolygonElementRenderer.cpp
        Source/Renderers/GuiFocusRectangleElementRenderer.cpp
        Source/Renderers/GuiColorizedTextElementRenderer.cpp
        Source/Renderers/GuiInnerShadowElementRenderer.cpp
        Source/Renderers/GGacLayoutProvider.cpp
        Source/Renderers/GuiGGacElementRenderer.cpp
	Source/GGacController.cpp
        Source/GGacWindow.cpp
        Source/GGacWindowListener.cpp
        Source/GGacHelper.cpp
        Source/GGacControllerListener.cpp
        Source/GGacView.cpp
        )
target_link_libraries(gGac ${GTK3_LIBRARIES})

include_directories(${GTK3_INCLUDE_DIRS} GacUI/Import Source Source/Renderers Source/Services)
list(APPEND FC_DEP_LIBS GacUI gGac)

add_subdirectory(Tests/GacUI_HelloWorlds/Cpp)
add_subdirectory(Tests/GacUI_HelloWorlds/CppXml)
add_subdirectory(Tests/GacUI_HelloWorlds/MVVM)
add_subdirectory(Tests/GacUI_Layout/Alignment)
add_subdirectory(Tests/GacUI_Layout/Flow)
add_subdirectory(Tests/GacUI_Layout/Responsive1)
add_subdirectory(Tests/GacUI_Layout/Responsive2)
add_subdirectory(Tests/GacUI_Layout/RichTextEmbedding)
add_subdirectory(Tests/GacUI_Layout/SharedSize)
add_subdirectory(Tests/GacUI_Layout/Stack)
add_subdirectory(Tests/GacUI_Layout/Table)
add_subdirectory(Tests/GacUI_Layout/TableSplitter)
add_subdirectory(Tests/GacUI_Xml/Binding_Bind)
add_subdirectory(Tests/GacUI_Xml/Binding_Eval)
add_subdirectory(Tests/GacUI_Xml/Binding_Format)
add_subdirectory(Tests/GacUI_Xml/Binding_Uri)
add_subdirectory(Tests/GacUI_Xml/Binding_ViewModel)
add_subdirectory(Tests/GacUI_Xml/Event_Cpp)
add_subdirectory(Tests/GacUI_Xml/Event_Script)
add_subdirectory(Tests/GacUI_Xml/Event_ViewModel)
add_subdirectory(Tests/GacUI_Xml/Instance_Control)
add_subdirectory(Tests/GacUI_Xml/Instance_MultipleWindows)
add_subdirectory(Tests/GacUI_Xml/Instance_Window)
add_subdirectory(Tests/GacUI_Xml/Member_Field)
add_subdirectory(Tests/GacUI_Xml/Member_Parameter)
add_subdirectory(Tests/GacUI_Xml/Member_Property)
add_subdirectory(Tests/GacUI_Xml/Misc_ImportFolder)
add_subdirectory(Tests/GacUI_Controls/AddressBook)
add_subdirectory(Tests/GacUI_Controls/Animation)
add_subdirectory(Tests/GacUI_Controls/CalculatorAndStateMachine)
add_subdirectory(Tests/GacUI_Controls/ColorPicker)
add_subdirectory(Tests/GacUI_Controls/ContainersAndButtons)
add_subdirectory(Tests/GacUI_Controls/DataGrid)
add_subdirectory(Tests/GacUI_Controls/DocumentEditorRibbon)
add_subdirectory(Tests/GacUI_Controls/DocumentEditorToolstrip)
add_subdirectory(Tests/GacUI_Controls/ListControls)
add_subdirectory(Tests/GacUI_Controls/Localization)
add_subdirectory(Tests/GacUI_Controls/MenuVisibility)
add_subdirectory(Tests/GacUI_Controls/ProgressAndAsync)
add_subdirectory(Tests/GacUI_Controls/QueryService)
add_subdirectory(Tests/GacUI_Controls/TextEditor)
add_subdirectory(Tests/GacUI_Controls/TriplePhaseImageButton)
add_subdirectory(Tests/GacUI_ControlTemplate/WindowSkin)

list(APPEND CATEGORIES GacUI_Controls GacUI_ControlTemplate GacUI_HelloWorlds GacUI_Layout GacUI_Xml)
foreach(CATEGORY IN LISTS CATEGORIES)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/GacUI/Tutorial/${CATEGORY}/UIRes
		${CMAKE_CURRENT_BINARY_DIR}/Tests/${CATEGORY}/UIRes)
endforeach()
