add_executable(MVVM
        UI/Source/HelloWorldPartialClasses.cpp UI/Source/HelloWorldPartialClasses.h  UI/Source/HelloWorld.h
        UI/Source/MainWindow.cpp UI/Source/MainWindow.h
		../../App.cpp Main.cpp)
target_link_libraries (MVVM ${FC_DEP_LIBS})