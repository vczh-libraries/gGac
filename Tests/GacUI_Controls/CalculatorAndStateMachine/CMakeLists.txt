project(CalculatorAndStateMachine)
add_executable(CalculatorAndStateMachine
        UI/Source/DemoPartialClasses.cpp UI/Source/DemoPartialClasses.h  UI/Source/Demo.h
		Main.cpp)
target_link_libraries (CalculatorAndStateMachine ${FC_DEP_LIBS})