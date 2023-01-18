project(Member_Parameter)
add_executable(Member_Parameter
    ../../../GacUI/Tutorial/GacUI_Xml/Member_Parameter/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Member_Parameter/Main.cpp
    ../../App.cpp)
target_link_libraries (Member_Parameter ${gGac_LIBRARIES})
