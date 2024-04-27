project(RichTextEmbedding)
add_executable(RichTextEmbedding
        ../../../Release/Tutorial/GacUI_Layout/RichTextEmbedding/UI/Source/DemoPartialClasses.cpp
        ../../../Release/Tutorial/GacUI_Layout/RichTextEmbedding/Main.cpp
		../../App.cpp)
target_link_libraries (RichTextEmbedding ${gGac_LIBRARIES})