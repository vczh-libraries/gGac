project(SharedSize)
add_executable(SharedSize
    ../../../Release/Tutorial/GacUI_Layout/SharedSize/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Layout/SharedSize/Main.cpp
    ../../App.cpp)
target_link_libraries (SharedSize ${gGac_LIBRARIES})
