add_executable(Flow
        ../../../Release/Tutorial/GacUI_Layout/Flow/UI/Source/DemoPartialClasses.cpp
        ../../../Release/Tutorial/GacUI_Layout/Flow/Main.cpp
		../../App.cpp)
target_link_libraries (Flow ${gGac_LIBRARIES})