# Put the split script into the build dir
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/cpp-httplib/split.py
        ${CMAKE_CURRENT_BINARY_DIR}/httplib/split.py COPYONLY
)
# Needs to be in the same dir as the python script
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/cpp-httplib/httplib.h
        ${CMAKE_CURRENT_BINARY_DIR}/httplib/httplib.h COPYONLY
)

execute_process(COMMAND python ${CMAKE_CURRENT_BINARY_DIR}/httplib/split.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/httplib
        ERROR_VARIABLE _httplib_split_error
)

if (_httplib_split_error)
    message(FATAL_ERROR "Failed when trying to split cpp-httplib with the Python script.\n${_httplib_split_error}")
endif ()

# split.py puts output in "out"
set(_httplib_build_includedir ${CMAKE_CURRENT_BINARY_DIR}/httplib/out)

add_library(httplib STATIC ${_httplib_build_includedir}/httplib.cc)
target_include_directories(httplib PUBLIC ${_httplib_build_includedir})
if(WIN32)
    set(_httplib_link_libs ws2_32 crypt32 cryptui)
endif ()
target_link_libraries(httplib PUBLIC ${_httplib_link_libs} ${BUNNY_RUNTIME_LIBS})
target_compile_definitions(httplib PRIVATE -DCPPHTTPLIB_OPENSSL_SUPPORT)