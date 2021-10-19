add_executable(Stack
        ../../../GacUI/Tutorial/GacUI_Layout/Stack/UI/Source/DemoPartialClasses.cpp
        ../../../GacUI/Tutorial/GacUI_Layout/Stack/Main.cpp
		../../App.cpp)
target_link_libraries (Stack ${FC_DEP_LIBS})