if (WIN32)
    set(BUNNY_IMGUI_BACKEND_SYSTEM_SRC imgui_impl_glfw.cpp)
endif ()

add_library(
        imgui STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui_demo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui_draw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui_tables.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/imgui_widgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_opengl3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/backends/${BUNNY_IMGUI_BACKEND_SYSTEM_SRC}
)
target_link_libraries(imgui PUBLIC ${BUNNY_RUNTIME_LIBS})
target_compile_definitions(imgui PRIVATE -DIMGUI_IMPL_OPENGL_ES2)
target_include_directories(
        imgui PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/backends
)