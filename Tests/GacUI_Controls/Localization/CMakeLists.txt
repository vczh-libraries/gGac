project(Localization)
add_executable(Localization
    ../../../Release/Tutorial/GacUI_Controls/Localization/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Controls/Localization/Main.cpp
    ../../App.cpp)
target_link_libraries (Localization ${gGac_LIBRARIES})
