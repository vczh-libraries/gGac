project(Localization)
add_executable(Localization
    ../../../GacUI/Tutorial/GacUI_Controls/Localization/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/Localization/Main.cpp
    ../../App.cpp)
target_link_libraries (Localization ${FC_DEP_LIBS})
