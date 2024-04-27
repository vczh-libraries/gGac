project(CppXml)
add_executable(CppXml
    ../../../Release/Tutorial/GacUI_HelloWorlds/CppXml/UI/Source/HelloWorldPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_HelloWorlds/CppXml/Main.cpp
    ../../App.cpp)
target_link_libraries (CppXml ${gGac_LIBRARIES})
