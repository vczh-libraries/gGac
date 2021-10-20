project(ContainersAndButtons)
add_executable(ContainersAndButtons
    ../../../GacUI/Tutorial/GacUI_Controls/ContainersAndButtons/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/ContainersAndButtons/Main.cpp
    ../../App.cpp)
target_link_libraries (ContainersAndButtons ${FC_DEP_LIBS})
