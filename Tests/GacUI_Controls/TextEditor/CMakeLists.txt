project(TextEditor)
add_executable(TextEditor
    ../../../GacUI/Tutorial/GacUI_Controls/TextEditor/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/TextEditor/UI/Source/AboutWindow.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/TextEditor/UI/Source/FindWindow.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/TextEditor/UI/Source/MainWindow.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/TextEditor/Main.cpp
    ../../App.cpp)
target_link_libraries (TextEditor ${gGac_LIBRARIES})
