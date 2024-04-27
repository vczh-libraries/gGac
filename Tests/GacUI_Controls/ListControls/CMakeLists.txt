project(ListControls)
add_executable(ListControls
    ../../../Release/Tutorial/GacUI_Controls/ListControls/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Controls/ListControls/Main.cpp
    ../../App.cpp)
target_link_libraries (ListControls ${gGac_LIBRARIES})
