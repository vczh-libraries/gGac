add_executable(Flow
        ../../../GacUI/Tutorial/GacUI_Layout/Flow/UI/Source/DemoPartialClasses.cpp
        ../../../GacUI/Tutorial/GacUI_Layout/Flow/Main.cpp
		../../App.cpp)
target_link_libraries (Flow ${FC_DEP_LIBS})