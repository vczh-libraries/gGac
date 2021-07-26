add_executable(Responsive2
        UI/Source/DemoPartialClasses.cpp UI/Source/DemoPartialClasses.h  UI/Source/Demo.h
		../../App.cpp Main.cpp)
target_link_libraries (Responsive2 ${FC_DEP_LIBS})