project(Binding_Format)
add_executable(Binding_Format
    ../../../GacUI/Tutorial/GacUI_Xml/Binding_Format/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Binding_Format/Main.cpp
    ../../App.cpp)
target_link_libraries (Binding_Format ${FC_DEP_LIBS})
