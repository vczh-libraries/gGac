cmake_minimum_required(VERSION 3.17)
project(gGac VERSION 1.2.0.0 DESCRIPTION "Linux port for GacLib")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG -gdwarf-4")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG -gdwarf-4")
add_compile_definitions(VCZH_DEBUG_NO_REFLECTION)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtkmm-3.0 sigc++-2.0)

add_library(GacUI SHARED
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

add_library(gGac SHARED
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
        Source/Renderers/GuiSolidBackgroundElementRenderer.cpp
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
		Source/GGacCursor.cpp
		)
target_link_libraries(gGac GacUI ${GTK3_LIBRARIES} X11)
include_directories(GacUI/Import Source Source/Renderers Source/Services ${GTK3_INCLUDE_DIRS})
include(GNUInstallDirs)

set_target_properties(gGac PROPERTIES
		VERSION ${PROJECT_VERSION}
		PUBLIC_HEADER "Source/Renderers/GGacRenderer.h")
install(TARGETS gGac
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/gGac)

set_target_properties(GacUI PROPERTIES
		VERSION ${PROJECT_VERSION}
		PUBLIC_HEADER "GacUI/Import/VlppOS.h;GacUI/Import/GacUI.h;GacUI/Import/VlppParser.h;GacUI/Import/GacUICompiler.h;GacUI/Import/VlppReflection.h;GacUI/Import/GacUIReflection.h;GacUI/Import/VlppRegex.h;GacUI/Import/Vlpp.h;GacUI/Import/VlppWorkflowCompiler.h;GacUI/Import/VlppGlrParser.h;GacUI/Import/VlppWorkflowLibrary.h;GacUI/Import/VlppGlrParserCompiler.h;GacUI/Import/VlppWorkflowRuntime.h;GacUI/Import/Skins/DarkSkin/DarkSkin.h")
install(TARGETS GacUI
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GacUI)

configure_file(gGac.pc.in gGac.pc @ONLY)
configure_file(GacUI.pc.in GacUI.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/gGac.pc ${CMAKE_BINARY_DIR}/GacUI.pc
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
