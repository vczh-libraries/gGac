project(Binding_Uri)
add_executable(Binding_Uri
    ../../../Release/Tutorial/GacUI_Xml/Binding_Uri/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Xml/Binding_Uri/Main.cpp
    ../../App.cpp)
target_link_libraries (Binding_Uri ${gGac_LIBRARIES})
