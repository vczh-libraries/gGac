project(Member_Field)
add_executable(Member_Field
    ../../../GacUI/Tutorial/GacUI_Xml/Member_Field/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Member_Field/Main.cpp
    ../../App.cpp)
target_link_libraries (Member_Field ${FC_DEP_LIBS})
