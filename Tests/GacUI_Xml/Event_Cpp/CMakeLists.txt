project(Event_Cpp)
add_executable(Event_Cpp
    ../../../Release/Tutorial/GacUI_Xml/Event_Cpp/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Xml/Event_Cpp/UI/Source/MainWindow.cpp
    ../../../Release/Tutorial/GacUI_Xml/Event_Cpp/Main.cpp
    ../../App.cpp)
target_link_libraries (Event_Cpp ${gGac_LIBRARIES})
