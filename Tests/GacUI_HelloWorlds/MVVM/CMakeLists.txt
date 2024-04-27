add_executable(MVVM
    ../../../Release/Tutorial/GacUI_HelloWorlds/MVVM/UI/Source/HelloWorldPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_HelloWorlds/MVVM/UI/Source/MainWindow.cpp
    ../../../Release/Tutorial/GacUI_HelloWorlds/MVVM/Main.cpp
	../../App.cpp)
target_link_libraries (MVVM ${gGac_LIBRARIES})