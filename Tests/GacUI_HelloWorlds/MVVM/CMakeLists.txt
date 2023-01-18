add_executable(MVVM
    ../../../GacUI/Tutorial/GacUI_HelloWorlds/MVVM/UI/Source/HelloWorldPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_HelloWorlds/MVVM/UI/Source/MainWindow.cpp
    ../../../GacUI/Tutorial/GacUI_HelloWorlds/MVVM/Main.cpp
	../../App.cpp)
target_link_libraries (MVVM ${gGac_LIBRARIES})