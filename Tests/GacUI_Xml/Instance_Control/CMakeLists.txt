project(Instance_Control)
add_executable(Instance_Control
    ../../../GacUI/Tutorial/GacUI_Xml/Instance_Control/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Instance_Control/Main.cpp
    ../../App.cpp)
target_link_libraries (Instance_Control ${FC_DEP_LIBS})
