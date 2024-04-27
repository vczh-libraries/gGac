project(DataGrid)
add_executable(DataGrid
    ../../../Release/Tutorial/GacUI_Controls/DataGrid/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Controls/DataGrid/Main.cpp
    ../../App.cpp)
target_link_libraries (DataGrid ${gGac_LIBRARIES})
