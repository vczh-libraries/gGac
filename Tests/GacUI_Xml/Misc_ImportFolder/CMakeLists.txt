project(Misc_ImportFolder)
add_executable(Misc_ImportFolder
    ../../../Release/Tutorial/GacUI_Xml/Misc_ImportFolder/ResBase/Source/ResBasePartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Xml/Misc_ImportFolder/ResDerived/Source/ResDerivedPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Xml/Misc_ImportFolder/Main.cpp
    ../../App.cpp)
target_link_libraries (Misc_ImportFolder ${gGac_LIBRARIES})
