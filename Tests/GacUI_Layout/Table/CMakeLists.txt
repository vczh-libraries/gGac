add_executable(Table
        ../../../Release/Tutorial/GacUI_Layout/Table/UI/Source/DemoPartialClasses.cpp
        ../../../Release/Tutorial/GacUI_Layout/Table/Main.cpp
		../../App.cpp)
target_link_libraries (Table ${gGac_LIBRARIES})