project(Cpp)
add_executable(Cpp
    ../../../GacUI/Tutorial/GacUI_HelloWorlds/Cpp/Main.cpp
    ../../App.cpp
    )
target_link_libraries (Cpp ${gGac_LIBRARIES})