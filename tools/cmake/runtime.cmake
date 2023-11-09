if (WIN32)
    if (CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(CMAKE_WINDOWS_ARCH_ABI "x86")
    elseif (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(CMAKE_WINDOWS_ARCH_ABI "x64")
    else ()
        message(FATAL_ERROR "unsupported windows arch abi!")
    endif ()

    add_library(EGL SHARED IMPORTED GLOBAL)
    set_target_properties(
            EGL PROPERTIES
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/EGL/${CMAKE_WINDOWS_ARCH_ABI}/libEGL.dll
            IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/EGL/${CMAKE_WINDOWS_ARCH_ABI}/libEGL.lib
    )

    add_library(GLESv2 SHARED IMPORTED GLOBAL)
    set_target_properties(
            GLESv2 PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/GLESv2/include
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/GLESv2/${CMAKE_WINDOWS_ARCH_ABI}/libGLESv2.dll
            IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/GLESv2/${CMAKE_WINDOWS_ARCH_ABI}/libGLESv2.lib
    )

    add_library(glfw3 SHARED IMPORTED GLOBAL)
    set_target_properties(
            glfw3 PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/glfw3/include
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/glfw3/${CMAKE_WINDOWS_ARCH_ABI}/glfw3.dll
            IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/glfw3/${CMAKE_WINDOWS_ARCH_ABI}/glfw3.lib
    )

    add_library(crypto SHARED IMPORTED GLOBAL)
    set_target_properties(
            crypto PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/openssl/${CMAKE_WINDOWS_ARCH_ABI}/include
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/openssl/${CMAKE_WINDOWS_ARCH_ABI}/libcrypto-1_1-x64.dll
            IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/openssl/${CMAKE_WINDOWS_ARCH_ABI}/libcrypto.lib
    )

    add_library(ssl SHARED IMPORTED GLOBAL)
    set_target_properties(
            ssl PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/openssl/${CMAKE_WINDOWS_ARCH_ABI}/include
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/openssl/${CMAKE_WINDOWS_ARCH_ABI}/libssl-1_1-x64.dll
            IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/openssl/${CMAKE_WINDOWS_ARCH_ABI}/libssl.lib
    )

    add_library(ffmpeg SHARED IMPORTED GLOBAL)
    set_target_properties(
            ffmpeg PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/ffmpeg/include
            IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/ffmpeg/${CMAKE_WINDOWS_ARCH_ABI}/ffmpeg-4.dll
            IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/runtime/ffmpeg/${CMAKE_WINDOWS_ARCH_ABI}/ffmpeg.lib
    )

    set(WR_RUNTIME_LIBS EGL GLESv2 glfw3 crypto ssl ffmpeg)
endif ()