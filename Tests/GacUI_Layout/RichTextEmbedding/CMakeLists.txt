project(RichTextEmbedding)
add_executable(RichTextEmbedding
        UI/Source/DemoPartialClasses.cpp UI/Source/DemoPartialClasses.h  UI/Source/Demo.h
		Main.cpp)
target_link_libraries (RichTextEmbedding ${FC_DEP_LIBS})