project(ColorPicker)
add_executable(ColorPicker
    ../../../Release/Tutorial/GacUI_Controls/ColorPicker/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Controls/ColorPicker/Main.cpp
    ../../App.cpp)
target_link_libraries (ColorPicker ${gGac_LIBRARIES})
