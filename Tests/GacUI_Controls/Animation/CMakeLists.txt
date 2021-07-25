project(Animation)
add_executable(Animation
        UI/Source/DemoPartialClasses.cpp UI/Source/DemoPartialClasses.h  UI/Source/Demo.h
		../../App.cpp Main.cpp)
target_link_libraries (Animation ${FC_DEP_LIBS})