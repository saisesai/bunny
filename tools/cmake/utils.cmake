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