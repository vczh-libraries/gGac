project(AddressBook)
add_executable(AddressBook
        UI/Source/DemoPartialClasses.cpp UI/Source/DemoPartialClasses.h  UI/Source/Demo.h
        UI/Source/MainWindow.cpp UI/Source/MainWindow.h  UI/Source/Demo.h
		Main.cpp)
target_link_libraries (AddressBook ${FC_DEP_LIBS})