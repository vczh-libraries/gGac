project(CppXml)
add_executable(CppXml
    ../../../GacUI/Tutorial/GacUI_HelloWorlds/CppXml/UI/Source/HelloWorldPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_HelloWorlds/CppXml/Main.cpp
    ../../App.cpp)
target_link_libraries (CppXml ${gGac_LIBRARIES})
