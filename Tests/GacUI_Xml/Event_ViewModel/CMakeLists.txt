project(Event_ViewModel)
add_executable(Event_ViewModel
    ../../../GacUI/Tutorial/GacUI_Xml/Event_ViewModel/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Event_ViewModel/Main.cpp
    ../../App.cpp)
target_link_libraries (Event_ViewModel ${FC_DEP_LIBS})
