project(QueryService)
add_executable(QueryService
    ../../../Release/Tutorial/GacUI_Controls/QueryService/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Controls/QueryService/Main.cpp
    ../../App.cpp)
target_link_libraries (QueryService ${gGac_LIBRARIES})
