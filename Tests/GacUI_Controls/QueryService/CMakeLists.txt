project(QueryService)
add_executable(QueryService
    ../../../GacUI/Tutorial/GacUI_Controls/QueryService/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/QueryService/Main.cpp
    ../../App.cpp)
target_link_libraries (QueryService ${FC_DEP_LIBS})
