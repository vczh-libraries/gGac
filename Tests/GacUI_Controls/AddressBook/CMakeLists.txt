project(AddressBook)
add_executable(AddressBook
        ../../../Release/Tutorial/GacUI_Controls/AddressBook/UI/Source/DemoPartialClasses.cpp
        ../../../Release/Tutorial/GacUI_Controls/AddressBook/UI/Source/MainWindow.cpp
        ../../../Release/Tutorial/GacUI_Controls/AddressBook/Main.cpp
		../../App.cpp)
target_link_libraries (AddressBook ${gGac_LIBRARIES})
