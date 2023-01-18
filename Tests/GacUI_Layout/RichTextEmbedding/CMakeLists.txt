project(RichTextEmbedding)
add_executable(RichTextEmbedding
        ../../../GacUI/Tutorial/GacUI_Layout/RichTextEmbedding/UI/Source/DemoPartialClasses.cpp
        ../../../GacUI/Tutorial/GacUI_Layout/RichTextEmbedding/Main.cpp
		../../App.cpp)
target_link_libraries (RichTextEmbedding ${gGac_LIBRARIES})