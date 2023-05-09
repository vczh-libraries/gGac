project(GlobalHotKey)
add_executable(GlobalHotKey
    ../../../GacUI/Tutorial/GacUI_Controls/GlobalHotKey/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/GlobalHotKey/Main.cpp
    ../../App.cpp)
target_link_libraries (GlobalHotKey ${gGac_LIBRARIES})
