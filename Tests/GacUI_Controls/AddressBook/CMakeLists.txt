project(AddressBook)
add_executable(AddressBook
        ../../../GacUI/Tutorial/GacUI_Controls/AddressBook/UI/Source/DemoPartialClasses.cpp
        ../../../GacUI/Tutorial/GacUI_Controls/AddressBook/UI/Source/MainWindow.cpp
        ../../../GacUI/Tutorial/GacUI_Controls/AddressBook/Main.cpp
		../../App.cpp)
target_link_libraries (AddressBook ${FC_DEP_LIBS})
