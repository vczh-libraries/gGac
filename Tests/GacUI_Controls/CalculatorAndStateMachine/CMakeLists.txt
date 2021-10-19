project(CalculatorAndStateMachine)
add_executable(CalculatorAndStateMachine
        ../../../GacUI/Tutorial/GacUI_Controls/CalculatorAndStateMachine/UI/Source/DemoPartialClasses.cpp
        ../../../GacUI/Tutorial/GacUI_Controls/CalculatorAndStateMachine/Main.cpp
		../../App.cpp)
target_link_libraries (CalculatorAndStateMachine ${FC_DEP_LIBS})