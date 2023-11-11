function(copy_runtime_dlls)
    if (NOT ${ARGC} EQUAL 1)
        message(FATAL_ERROR "invalid args to call copy_runtime_dlls!")
    endif ()

    add_custom_command(TARGET ${ARGV0} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E
            copy $<TARGET_RUNTIME_DLLS:${ARGV0}> $<TARGET_FILE_DIR:${ARGV0}>
            COMMAND_EXPAND_LISTS
    )
endfunction()

function(copy_required_assets_desktop)
    set(BUNNY_ASSETS_ORI_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../assets)
    set(BUNNY_ASSETS_DST_PATH ${CMAKE_CURRENT_BINARY_DIR}/assets)
    configure_file(
            "${BUNNY_ASSETS_ORI_PATH}/fonts/YaHei Consolas Hybrid 1.12.ttf"
            "${BUNNY_ASSETS_DST_PATH}/fonts/YaHei Consolas Hybrid 1.12.ttf" COPYONLY
    )
endfunction()