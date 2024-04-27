project(MenuVisibility)
add_executable(MenuVisibility
    ../../../Release/Tutorial/GacUI_Controls/MenuVisibility/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Controls/MenuVisibility/Main.cpp
    ../../App.cpp)
target_link_libraries (MenuVisibility ${gGac_LIBRARIES})
