project(Binding_ViewModel)
add_executable(Binding_ViewModel
    ../../../GacUI/Tutorial/GacUI_Xml/Binding_ViewModel/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Binding_ViewModel/Main.cpp
    ../../App.cpp)
target_link_libraries (Binding_ViewModel ${gGac_LIBRARIES})
