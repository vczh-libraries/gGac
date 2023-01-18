project(TableSplitter)
add_executable(TableSplitter
    ../../../GacUI/Tutorial/GacUI_Layout/TableSplitter/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Layout/TableSplitter/Main.cpp
    ../../App.cpp)
target_link_libraries (TableSplitter ${gGac_LIBRARIES})
