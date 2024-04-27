project(Member_Field)
add_executable(Member_Field
    ../../../Release/Tutorial/GacUI_Xml/Member_Field/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Xml/Member_Field/UI/Source/MainWindow.cpp
    ../../../Release/Tutorial/GacUI_Xml/Member_Field/Main.cpp
    ../../App.cpp)
target_link_libraries (Member_Field ${gGac_LIBRARIES})
