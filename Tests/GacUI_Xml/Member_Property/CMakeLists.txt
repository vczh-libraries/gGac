project(Member_Property)
add_executable(Member_Property
    ../../../Release/Tutorial/GacUI_Xml/Member_Property/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Xml/Member_Property/Main.cpp
    ../../App.cpp)
target_link_libraries (Member_Property ${gGac_LIBRARIES})
