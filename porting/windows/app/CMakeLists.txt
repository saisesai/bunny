cmake_minimum_required(VERSION 3.15)

project(bunny-app)

add_subdirectory(../../../ bunny)

add_executable(bunny-app src/main.cc)
target_link_libraries(bunny-app PRIVATE bunny)

copy_runtime_dlls(bunny-app)
copy_required_assets_desktop()