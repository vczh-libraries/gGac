project(Binding_Format)
add_executable(Binding_Format
    ../../../Release/Tutorial/GacUI_Xml/Binding_Format/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Xml/Binding_Format/Main.cpp
    ../../App.cpp)
target_link_libraries (Binding_Format ${gGac_LIBRARIES})
