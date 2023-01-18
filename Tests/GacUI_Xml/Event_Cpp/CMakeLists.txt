project(Event_Cpp)
add_executable(Event_Cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Event_Cpp/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Event_Cpp/UI/Source/MainWindow.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Event_Cpp/Main.cpp
    ../../App.cpp)
target_link_libraries (Event_Cpp ${gGac_LIBRARIES})
