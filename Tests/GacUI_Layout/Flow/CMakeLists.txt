add_executable(Flow
        UI/Source/DemoPartialClasses.cpp UI/Source/DemoPartialClasses.h  UI/Source/Demo.h
		../../App.cpp Main.cpp)
target_link_libraries (Flow ${FC_DEP_LIBS})