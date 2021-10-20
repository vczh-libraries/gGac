project(gGac)
cmake_minimum_required(VERSION 3.16)
add_compile_definitions(VCZH_DEBUG_NO_REFLECTION)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtkmm-3.0)

add_library(GacUI
        GacUI/Import/GacUI.cpp
        GacUI/Import/Vlpp.cpp
        GacUI/Import/VlppOS.cpp
        GacUI/Import/VlppRegex.cpp
        GacUI/Import/VlppReflection.cpp
        GacUI/Import/VlppParser.cpp
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

ADD_SUBDIRECTORY(Tests/GacUI_HelloWorlds/Cpp)
ADD_SUBDIRECTORY(Tests/GacUI_HelloWorlds/CppXml)
ADD_SUBDIRECTORY(Tests/GacUI_HelloWorlds/MVVM)
ADD_SUBDIRECTORY(Tests/GacUI_Layout/Alignment)
ADD_SUBDIRECTORY(Tests/GacUI_Layout/Flow)
ADD_SUBDIRECTORY(Tests/GacUI_Layout/Responsive1)
ADD_SUBDIRECTORY(Tests/GacUI_Layout/Responsive2)
ADD_SUBDIRECTORY(Tests/GacUI_Layout/RichTextEmbedding)
ADD_SUBDIRECTORY(Tests/GacUI_Layout/SharedSize)
ADD_SUBDIRECTORY(Tests/GacUI_Layout/Stack)
ADD_SUBDIRECTORY(Tests/GacUI_Layout/Table)
ADD_SUBDIRECTORY(Tests/GacUI_Layout/TableSplitter)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Binding_Bind)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Binding_Eval)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Binding_Format)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Binding_Uri)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Binding_ViewModel)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Event_Cpp)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Event_Script)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Event_ViewModel)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Instance_Control)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Instance_MultipleWindows)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Instance_Window)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Member_Field)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Member_Parameter)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Member_Property)
ADD_SUBDIRECTORY(Tests/GacUI_Xml/Misc_ImportFolder)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/AddressBook)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/Animation)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/CalculatorAndStateMachine)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/ColorPicker)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/ContainersAndButtons)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/DataGrid)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/DocumentEditorRibbon)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/DocumentEditorToolstrip)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/ListControls)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/Localization)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/MenuVisibility)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/ProgressAndAsync)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/QueryService)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/TextEditor)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/TriplePhaseImageButton)