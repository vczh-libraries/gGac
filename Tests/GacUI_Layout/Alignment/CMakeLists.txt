project(Alignment)
add_executable(Alignment
    ../../../Release/Tutorial/GacUI_Layout/Alignment/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Layout/Alignment/Main.cpp
    ../../App.cpp)
target_link_libraries (Alignment ${gGac_LIBRARIES})
