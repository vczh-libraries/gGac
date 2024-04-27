project(Binding_Eval)
add_executable(Binding_Eval
    ../../../Release/Tutorial/GacUI_Xml/Binding_Eval/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Xml/Binding_Eval/Main.cpp
    ../../App.cpp)
target_link_libraries (Binding_Eval ${gGac_LIBRARIES})
