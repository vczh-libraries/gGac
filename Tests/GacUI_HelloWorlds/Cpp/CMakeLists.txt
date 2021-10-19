project(Cpp)
add_executable(Cpp
    ../../App.cpp
    ../../../GacUI/Tutorial/GacUI_HelloWorlds/Cpp/Main.cpp
    )
target_link_libraries (Cpp ${FC_DEP_LIBS})