project(Binding_Uri)
add_executable(Binding_Uri
    ../../../GacUI/Tutorial/GacUI_Xml/Binding_Uri/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Binding_Uri/Main.cpp
    ../../App.cpp)
target_link_libraries (Binding_Uri ${FC_DEP_LIBS})
