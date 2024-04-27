add_executable(Stack
        ../../../Release/Tutorial/GacUI_Layout/Stack/UI/Source/DemoPartialClasses.cpp
        ../../../Release/Tutorial/GacUI_Layout/Stack/Main.cpp
		../../App.cpp)
target_link_libraries (Stack ${gGac_LIBRARIES})