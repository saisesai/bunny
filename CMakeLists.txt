cmake_minimum_required(VERSION 3.15)

project(white-rabbit)

include(tools/cmake/utils.cmake)
include(tools/cmake/runtime.cmake)
include(tools/cmake/lua.cmake)
include(tools/cmake/imgui.cmake)
include(tools/cmake/httplib.cmake)

add_library(white-rabbit src/app.cc)
target_link_libraries(white-rabbit PUBLIC ${WR_RUNTIME_LIBS} lua imgui httplib)