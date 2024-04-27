project(Event_Script)
add_executable(Event_Script
    ../../../Release/Tutorial/GacUI_Xml/Event_Script/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Xml/Event_Script/Main.cpp
    ../../App.cpp)
target_link_libraries (Event_Script ${gGac_LIBRARIES})
