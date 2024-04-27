add_executable(Responsive1
        ../../../Release/Tutorial/GacUI_Layout/Responsive1/UI/Source/DemoPartialClasses.cpp
        ../../../Release/Tutorial/GacUI_Layout/Responsive1/Main.cpp
		../../App.cpp)
target_link_libraries (Responsive1 ${gGac_LIBRARIES})