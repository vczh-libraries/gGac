project(DataGrid)
add_executable(DataGrid
    ../../../GacUI/Tutorial/GacUI_Controls/DataGrid/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/DataGrid/Main.cpp
    ../../App.cpp)
target_link_libraries (DataGrid ${FC_DEP_LIBS})
