project(TextEditor)
add_executable(TextEditor
    ../../../Release/Tutorial/GacUI_Controls/TextEditor/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Controls/TextEditor/UI/Source/AboutWindow.cpp
    ../../../Release/Tutorial/GacUI_Controls/TextEditor/UI/Source/FindWindow.cpp
    ../../../Release/Tutorial/GacUI_Controls/TextEditor/UI/Source/MainWindow.cpp
    ../../../Release/Tutorial/GacUI_Controls/TextEditor/Main.cpp
    ../../App.cpp)
target_link_libraries (TextEditor ${gGac_LIBRARIES})
