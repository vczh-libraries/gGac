project(Binding_Eval)
add_executable(Binding_Eval
    ../../../GacUI/Tutorial/GacUI_Xml/Binding_Eval/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Binding_Eval/Main.cpp
    ../../App.cpp)
target_link_libraries (Binding_Eval ${FC_DEP_LIBS})
