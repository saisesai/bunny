cmake_minimum_required(VERSION 3.15)

project(bunny)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(tools/cmake/utils.cmake)
include(tools/cmake/runtime.cmake)
include(tools/cmake/lua.cmake)
include(tools/cmake/imgui.cmake)
include(tools/cmake/httplib.cmake)

# bunny lib source files
set(
        BUNNY_LIB_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/engine.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/file_system.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/image.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/logger.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/resource_manager.cc
)

# bunny lib include paths
set(
        BUNNY_LIB_INCS
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# bunny lib platform implement sources
if (WIN32)
    set(
            BUNNY_IMPL_SRCS
            ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/impl/impl_file_system_windows.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/porting/windows/impl/impl_logger_windows.cc
    )
elseif (ANDROID)
    set(
            BUNNY_IMPL_SRCS
    )
endif ()

add_library(bunny STATIC ${BUNNY_LIB_SRCS} ${BUNNY_IMPL_SRCS})
target_link_libraries(bunny PUBLIC ${BUNNY_RUNTIME_LIBS} lua imgui httplib)
target_include_directories(bunny PUBLIC ${BUNNY_LIB_INCS})
if (WIN32)
    target_compile_definitions(bunny PRIVATE -D_CRT_SECURE_NO_WARNINGS)
endif ()