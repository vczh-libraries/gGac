project(ColorPicker)
add_executable(ColorPicker
    ../../../GacUI/Tutorial/GacUI_Controls/ColorPicker/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/ColorPicker/Main.cpp
    ../../App.cpp)
target_link_libraries (ColorPicker ${gGac_LIBRARIES})
