project(MenuVisibility)
add_executable(MenuVisibility
    ../../../GacUI/Tutorial/GacUI_Controls/MenuVisibility/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/MenuVisibility/Main.cpp
    ../../App.cpp)
target_link_libraries (MenuVisibility ${FC_DEP_LIBS})
