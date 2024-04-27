project(GlobalHotKey)
add_executable(GlobalHotKey
    ../../../Release/Tutorial/GacUI_Controls/GlobalHotKey/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Controls/GlobalHotKey/Main.cpp
    ../../App.cpp)
target_link_libraries (GlobalHotKey ${gGac_LIBRARIES})
