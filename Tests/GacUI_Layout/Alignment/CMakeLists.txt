project(Alignment)
add_executable(Alignment
    ../../../GacUI/Tutorial/GacUI_Layout/Alignment/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Layout/Alignment/Main.cpp
    ../../App.cpp)
target_link_libraries (Alignment ${gGac_LIBRARIES})
