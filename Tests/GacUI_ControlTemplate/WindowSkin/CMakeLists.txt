project(WindowSkin)
add_executable(WindowSkin
    ../../../Release/Tutorial/GacUI_ControlTemplate/WindowSkin/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_ControlTemplate/WindowSkin/UI/Source/MainWindow.cpp
    ../../../Release/Tutorial/GacUI_ControlTemplate/WindowSkin/Main.cpp
    ../../App.cpp)
target_link_libraries (WindowSkin ${gGac_LIBRARIES})
