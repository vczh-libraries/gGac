project(Binding_Bind)
add_executable(Binding_Bind
    ../../../GacUI/Tutorial/GacUI_Xml/Binding_Bind/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Binding_Bind/Main.cpp
    ../../App.cpp)
target_link_libraries (Binding_Bind ${FC_DEP_LIBS})
