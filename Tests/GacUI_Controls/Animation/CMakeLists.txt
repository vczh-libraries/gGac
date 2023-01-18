project(Animation)
add_executable(Animation
        ../../../GacUI/Tutorial/GacUI_Controls/Animation/UI/Source/DemoPartialClasses.cpp
        ../../../GacUI/Tutorial/GacUI_Controls/Animation/Main.cpp
		../../App.cpp)
target_link_libraries (Animation ${gGac_LIBRARIES})