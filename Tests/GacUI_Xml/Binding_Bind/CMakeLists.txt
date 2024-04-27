project(Binding_Bind)
add_executable(Binding_Bind
    ../../../Release/Tutorial/GacUI_Xml/Binding_Bind/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Xml/Binding_Bind/Main.cpp
    ../../App.cpp)
target_link_libraries (Binding_Bind ${gGac_LIBRARIES})
