project(Event_ViewModel)
add_executable(Event_ViewModel
    ../../../Release/Tutorial/GacUI_Xml/Event_ViewModel/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Xml/Event_ViewModel/Main.cpp
    ../../App.cpp)
target_link_libraries (Event_ViewModel ${gGac_LIBRARIES})
