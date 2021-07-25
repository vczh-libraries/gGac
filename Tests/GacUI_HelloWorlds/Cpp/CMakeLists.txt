project(Cpp)
add_executable(Cpp ../../App.cpp Main.cpp)
target_link_libraries (Cpp ${FC_DEP_LIBS})