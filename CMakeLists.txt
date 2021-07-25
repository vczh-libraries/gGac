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
		GGacController.cpp 
        Services/GGacCallbackService.cpp 
        Services/GGacInputService.cpp 
        Services/GGacAsyncService.cpp 
        Services/GGacImageService.cpp 
        Services/GGacDialogService.cpp 
        Services/GGacResourceService.cpp 
        Services/GGacScreenService.cpp 
        Services/GGacClipboardService.cpp 
        GGacWindow.cpp 
        GGacWindowListener.cpp 
        GGacHelper.cpp 
        GGacControllerListener.cpp 
        Renderers/GuiSolidBorderElementRenderer.cpp 
        Renderers/GGacRenderer.cpp 
        Renderers/Gui3DBorderElementRenderer.cpp 
        Renderers/GuiSoldBackgroundElementRenderer.cpp 
        Renderers/GuiSolidLabelElementRenderer.cpp 
        Renderers/Gui3DSplitterElementRenderer.cpp 
        Renderers/GuiGradientBackgroundElementRenderer.cpp 
        Renderers/GuiImageFrameElementRenderer.cpp 
        Renderers/GuiPolygonElementRenderer.cpp 
        Renderers/GuiFocusRectangleElementRenderer.cpp 
        Renderers/GuiColorizedTextElementRenderer.cpp 
        Renderers/GuiInnerShadowElementRenderer.cpp 
        Renderers/GGacLayoutProvider.cpp 
        GGacView.cpp 
        Renderers/GuiGGacElementRenderer.cpp 
        )
target_link_libraries(gGac ${GTK3_LIBRARIES})

include_directories(${GTK3_INCLUDE_DIRS} GacUI/Import Renderers Services)
list(APPEND FC_DEP_LIBS GacUI gGac)

ADD_SUBDIRECTORY(Tests/GacUI_Controls/AddressBook)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/Animation)
ADD_SUBDIRECTORY(Tests/GacUI_Controls/CalculatorAndStateMachine)
ADD_SUBDIRECTORY(Tests/GacUI_Layout/RichTextEmbedding)
ADD_SUBDIRECTORY(Tests/GacUI_HelloWorlds/Cpp)
ADD_SUBDIRECTORY(Tests/GacUI_HelloWorlds/MVVM)
