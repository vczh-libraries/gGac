project(ContainersAndButtons)
add_executable(ContainersAndButtons
    ../../../Release/Tutorial/GacUI_Controls/ContainersAndButtons/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Controls/ContainersAndButtons/Main.cpp
    ../../App.cpp)
target_link_libraries (ContainersAndButtons ${gGac_LIBRARIES})
