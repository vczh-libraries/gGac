project(TriplePhaseImageButton)
add_executable(TriplePhaseImageButton
    ../../../Release/Tutorial/GacUI_Controls/TriplePhaseImageButton/UI/Source/DemoPartialClasses.cpp
    ../../../Release/Tutorial/GacUI_Controls/TriplePhaseImageButton/Main.cpp
    ../../App.cpp)
target_link_libraries (TriplePhaseImageButton ${gGac_LIBRARIES})
