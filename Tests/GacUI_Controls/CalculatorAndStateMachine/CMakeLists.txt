project(CalculatorAndStateMachine)
add_executable(CalculatorAndStateMachine
        ../../../Release/Tutorial/GacUI_Controls/CalculatorAndStateMachine/UI/Source/DemoPartialClasses.cpp
        ../../../Release/Tutorial/GacUI_Controls/CalculatorAndStateMachine/Main.cpp
		../../App.cpp)
target_link_libraries (CalculatorAndStateMachine ${gGac_LIBRARIES})