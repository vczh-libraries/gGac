project(Misc_ImportFolder)
add_executable(Misc_ImportFolder
    ../../../GacUI/Tutorial/GacUI_Xml/Misc_ImportFolder/ResBase/Source/ResBasePartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Misc_ImportFolder/ResDerived/Source/ResDerivedPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Xml/Misc_ImportFolder/Main.cpp
    ../../App.cpp)
target_link_libraries (Misc_ImportFolder ${FC_DEP_LIBS})
