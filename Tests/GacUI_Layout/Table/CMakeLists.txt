add_executable(Table
        ../../../GacUI/Tutorial/GacUI_Layout/Table/UI/Source/DemoPartialClasses.cpp
        ../../../GacUI/Tutorial/GacUI_Layout/Table/Main.cpp
		../../App.cpp)
target_link_libraries (Table ${gGac_LIBRARIES})