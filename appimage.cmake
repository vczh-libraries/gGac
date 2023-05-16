function(make_appimage)
	set(optional)
	set(args EXE NAME DIR_ICON ICON OUTPUT_NAME OUTPUT_ARCH CROSSCOMP) 
	set(list_args ASSETS)
	cmake_parse_arguments(
		PARSE_ARGV 0
		ARGS
		"${optional}"
		"${args}"
		"${list_args}"
	)

	if(${ARGS_UNPARSED_ARGUMENTS})
		message(WARNING "Unparsed arguments: ${ARGS_UNPARSED_ARGUMENTS}")
	endif()


    # download AppImageTool if needed (TODO: non-x86 build machine?)
    SET(AIT_PATH "${CMAKE_BINARY_DIR}/AppImageTool-x86_64.AppImage" CACHE INTERNAL "")
    if (NOT EXISTS "${AIT_PATH}")
        file(DOWNLOAD https://github.com/AppImage/AppImageKit/releases/download/continuous/appimagetool-x86_64.AppImage "${AIT_PATH}")
        execute_process(COMMAND chmod +x ${AIT_PATH})
    endif()
	if(ARGS_CROSSCOMP)	# need to also download runtime
		SET(AIT_RUNTIME_PATH "${CMAKE_BINARY_DIR}/runtime-${ARGS_OUTPUT_ARCH}" CACHE INTERNAL "")
		if (NOT EXISTS "${AIT_RUNTIME_PATH}")
			file(DOWNLOAD https://github.com/AppImage/AppImageKit/releases/download/continuous/runtime-${ARGS_OUTPUT_ARCH} "${AIT_RUNTIME_PATH}")
		endif()
	endif()

    # make the AppDir
    set(APPDIR "${CMAKE_BINARY_DIR}/AppDir")
    file(REMOVE_RECURSE "${APPDIR}")       # remove if leftover
    file(MAKE_DIRECTORY "${APPDIR}")

    # copy executable to appdir
    file(COPY "${ARGS_EXE}" DESTINATION "${APPDIR}" FOLLOW_SYMLINK_CHAIN)
    get_filename_component(EXE_NAME "${ARGS_EXE}" NAME)

    # create the script that will launch the AppImage
file(WRITE "${APPDIR}/AppRun" 
"#!/bin/sh
cd \"$(dirname \"$0\")\";
./${EXE_NAME} $@"
    )
    execute_process(COMMAND chmod +x "${APPDIR}/AppRun")
    
    # copy assets to appdir
    foreach(ITEM ${ARGS_ASSETS})
        if(EXISTS ${ITEM})
            file(COPY ${ITEM} DESTINATION "${APPDIR}")
        endif()
    endforeach()

    # copy icon thumbnail
    file(COPY ${ARGS_DIR_ICON} DESTINATION "${APPDIR}")
    get_filename_component(THUMB_NAME "${ARGS_DIR_ICON}" NAME)
    file(RENAME "${APPDIR}/${THUMB_NAME}" "${APPDIR}/.DirIcon")

    # copy icon highres
    file(COPY ${ARGS_ICON} DESTINATION "${APPDIR}")
    get_filename_component(ICON_NAME "${ARGS_ICON}" NAME)
    get_filename_component(ICON_EXT "${ARGS_ICON}" EXT)
    file(RENAME "${APPDIR}/${ICON_NAME}" "${APPDIR}/${ARGS_NAME}${ICON_EXT}")

    # Create the .desktop file
    file(WRITE "${APPDIR}/${ARGS_NAME}.desktop" 
    "[Desktop Entry]
Type=Application
Name=${ARGS_NAME}
Icon=${ARGS_NAME}
Categories=X-None;"    
    )

    # Invoke AppImageTool
    if(ARGS_CROSSCOMP)
    	# when cross-compiling, set runtime file
    	set(AIT_RUNTIME "--runtime-file" CACHE INTERNAL "")
    endif()
    execute_process(COMMAND ${AIT_PATH} ${APPDIR} ${ARGS_OUTPUT_NAME} ${AIT_RUNTIME} ${AIT_RUNTIME_PATH})
    file(REMOVE_RECURSE "${APPDIR}")

endfunction()
