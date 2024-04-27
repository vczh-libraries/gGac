project(Instance_Control)
add_executable(Instance_Control
    ../../../Release/Tutorial/GacUI_Xml/Instance_Control/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Xml/Instance_Control/Main.cpp
    ../../App.cpp)
target_link_libraries (Instance_Control ${gGac_LIBRARIES})
