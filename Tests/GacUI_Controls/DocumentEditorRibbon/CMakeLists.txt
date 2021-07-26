project(DocumentEditorRibbon)
add_executable(DocumentEditorRibbon
		UI/Source/DocumentEditorBase.cpp UI/Source/DocumentEditorBase.h
		UI/Source/EditorBasePartialClasses.cpp UI/Source/EditorBasePartialClasses.h UI/Source/EditorBase.h
		UI/Source/EditorRibbonPartialClasses.cpp UI/Source/EditorRibbonPartialClasses.h UI/Source/EditorRibbon.h
		../../App.cpp Main.cpp)
target_link_libraries (DocumentEditorRibbon ${FC_DEP_LIBS})