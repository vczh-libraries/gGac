project(Animation)
add_executable(Animation
        ../../../Release/Tutorial/GacUI_Controls/Animation/UI/Source/DemoPartialClasses.cpp
        ../../../Release/Tutorial/GacUI_Controls/Animation/Main.cpp
		../../App.cpp)
target_link_libraries (Animation ${gGac_LIBRARIES})