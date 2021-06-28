cmake_minimum_required(VERSION 3.19)
project(gGac)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_library(GacUI GacUI/Import/GacUI.cpp GacUI/Import/GacUICompiler.cpp GacUI/Import/Vlpp.cpp
        GacUI/Import/VlppOS.cpp GacUI/Import/VlppParser.cpp GacUI/Import/VlppRegex.cpp GacUI/Import/VlppWorkflowCompiler.cpp
        GacUI/Import/VlppWorkflowLibrary.cpp GacUI/Import/VlppWorkflowRuntime.cpp)

include_directories(${GTK3_INCLUDE_DIRS} GacUI/Import)
link_directories(${GTK3_LIBRARY_DIRS} GacUI)
list(APPEND FC_DEP_LIBS ${GTK3_LIBRARIES} GacUI)

add_executable(gGac main.cpp GGacController.cpp GGacController.h Services/GGacCallbackService.cpp Services/GGacCallbackService.h Services/GGacInputService.cpp Services/GGacInputService.h Services/GGacAsyncService.cpp Services/GGacAsyncService.h Services/GGacImageService.cpp Services/GGacImageService.h Services/GGacDialogService.cpp Services/GGacDialogService.h Services/GGacResourceService.cpp Services/GGacResourceService.h Services/GGacScreenService.cpp Services/GGacScreenService.h Services/GGacClipboardService.cpp Services/GGacClipboardService.h GGacWindow.cpp GGacWindow.h GGacHelper.cpp GGacHelper.h GGacControllerListener.cpp GGacControllerListener.h Renderers/GuiSolidBorderElementRenderer.cpp Renderers/GuiSolidBorderElementRenderer.h Renderers/GGacRenderer.cpp Renderers/GGacRenderer.h Renderers/Gui3DBorderElementRenderer.cpp Renderers/Gui3DBorderElementRenderer.h Renderers/GuiSoldBackgroundElementRenderer.cpp Renderers/GuiSoldBackgroundElementRenderer.h Renderers/GuiSolidLabelElementRenderer.cpp Renderers/GuiSolidLabelElementRenderer.h Renderers/Gui3DSplitterElementRenderer.cpp Renderers/Gui3DSplitterElementRenderer.h Renderers/GuiGradientBackgroundElementRenderer.cpp Renderers/GuiGradientBackgroundElementRenderer.h Renderers/GuiImageFrameElementRenderer.cpp Renderers/GuiImageFrameElementRenderer.h Renderers/GuiPolygonElementRenderer.cpp Renderers/GuiPolygonElementRenderer.h Renderers/GuiFocusRectangleElementRenderer.cpp Renderers/GuiFocusRectangleElementRenderer.h Renderers/GuiColorizedTextElementRenderer.cpp Renderers/GuiColorizedTextElementRenderer.h Renderers/GuiInnerShadowElementRenderer.cpp Renderers/GuiInnerShadowElementRenderer.h)
target_link_libraries (gGac ${FC_DEP_LIBS})
