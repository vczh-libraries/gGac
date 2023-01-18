project(WindowSkin)
add_executable(WindowSkin
    ../../../GacUI/Tutorial/GacUI_ControlTemplate/WindowSkin/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_ControlTemplate/WindowSkin/UI/Source/MainWindow.cpp
    ../../../GacUI/Tutorial/GacUI_ControlTemplate/WindowSkin/Main.cpp
    ../../App.cpp)
target_link_libraries (WindowSkin ${gGac_LIBRARIES})
