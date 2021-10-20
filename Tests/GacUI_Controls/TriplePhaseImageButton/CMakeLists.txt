project(TriplePhaseImageButton)
add_executable(TriplePhaseImageButton
    ../../../GacUI/Tutorial/GacUI_Controls/TriplePhaseImageButton/UI/Source/DemoPartialClasses.cpp
    ../../../GacUI/Tutorial/GacUI_Controls/TriplePhaseImageButton/Main.cpp
    ../../App.cpp)
target_link_libraries (TriplePhaseImageButton ${FC_DEP_LIBS})
