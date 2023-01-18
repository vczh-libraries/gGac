project(Instance_Window)
add_executable(Instance_Window
    ../../../GacUI/Tutorial/GacUI_Xml/Instance_Window/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Instance_Window/Main.cpp
    ../../App.cpp)
target_link_libraries (Instance_Window ${gGac_LIBRARIES})
