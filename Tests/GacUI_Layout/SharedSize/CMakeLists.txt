project(SharedSize)
add_executable(SharedSize
    ../../../GacUI/Tutorial/GacUI_Layout/SharedSize/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Layout/SharedSize/Main.cpp
    ../../App.cpp)
target_link_libraries (SharedSize ${gGac_LIBRARIES})
