project(ProgressAndAsync)
add_executable(ProgressAndAsync
    ../../../Release/Tutorial/GacUI_Controls/ProgressAndAsync/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Controls/ProgressAndAsync/Main.cpp
    ../../App.cpp)
target_link_libraries (ProgressAndAsync ${gGac_LIBRARIES})
