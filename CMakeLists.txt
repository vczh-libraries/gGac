cmake_minimum_required(VERSION 3.19)
project(gGac)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS} GacUI/Import)
link_directories(${GTK3_LIBRARY_DIRS})
list(APPEND FC_DEP_LIBS ${GTK3_LIBRARIES})

add_executable(wlGac main.cpp GGacController.cpp GGacController.h Services/GGacCallbackService.cpp Services/GGacCallbackService.h Services/GGacInputService.cpp Services/GGacInputService.h Services/GGacAsyncService.cpp Services/GGacAsyncService.h Services/GGacImageService.cpp Services/GGacImageService.h Services/GGacDialogService.cpp Services/GGacDialogService.h Services/GGacResourceService.cpp Services/GGacResourceService.h Services/GGacScreenService.cpp Services/GGacScreenService.h Services/GGacClipboardService.cpp Services/GGacClipboardService.h GGacWindow.cpp GGacWindow.h GGacHelper.cpp GGacHelper.h GGacControllerListener.cpp GGacControllerListener.h Renderers/GuiSolidBorderElementRenderer.cpp Renderers/GuiSolidBorderElementRenderer.h Renderers/GGacRenderer.cpp Renderers/GGacRenderer.h Renderers/Gui3DBorderElementRenderer.cpp Renderers/Gui3DBorderElementRenderer.h Renderers/GuiSoldBackgroundElementRenderer.cpp Renderers/GuiSoldBackgroundElementRenderer.h Renderers/GuiSolidLabelElementRenderer.cpp Renderers/GuiSolidLabelElementRenderer.h)
target_link_libraries (wlGac ${FC_DEP_LIBS})
