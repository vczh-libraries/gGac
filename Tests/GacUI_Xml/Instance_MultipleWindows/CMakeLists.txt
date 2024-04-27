project(Instance_MultipleWindows)
add_executable(Instance_MultipleWindows
    ../../../Release/Tutorial/GacUI_Xml/Instance_MultipleWindows/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Xml/Instance_MultipleWindows/UI/Source/MainWindow.cpp
    ../../../Release/Tutorial/GacUI_Xml/Instance_MultipleWindows/Main.cpp
    ../../App.cpp)
target_link_libraries (Instance_MultipleWindows ${gGac_LIBRARIES})
