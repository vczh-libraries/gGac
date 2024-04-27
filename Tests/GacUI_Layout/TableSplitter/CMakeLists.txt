project(TableSplitter)
add_executable(TableSplitter
    ../../../Release/Tutorial/GacUI_Layout/TableSplitter/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Layout/TableSplitter/Main.cpp
    ../../App.cpp)
target_link_libraries (TableSplitter ${gGac_LIBRARIES})
