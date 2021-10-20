project(Instance_MultipleWindows)
add_executable(Instance_MultipleWindows
    ../../../GacUI/Tutorial/GacUI_Xml/Instance_MultipleWindows/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Instance_MultipleWindows/Main.cpp
    ../../App.cpp)
target_link_libraries (Instance_MultipleWindows ${FC_DEP_LIBS})
