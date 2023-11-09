cmake_minimum_required(VERSION 3.15)

project(white-rabbit-app)

add_subdirectory(../../../ white-rabbit)

add_executable(white-rabbit-app src/main.cc)
target_link_libraries(white-rabbit-app PRIVATE white-rabbit)

copy_runtime_dlls(white-rabbit-app)