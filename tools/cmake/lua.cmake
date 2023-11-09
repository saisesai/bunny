add_library(
        lua STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lapi.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lcode.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lctype.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/ldebug.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/ldo.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/ldump.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lfunc.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lgc.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/llex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lmem.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lobject.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lopcodes.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lparser.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lstate.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lstring.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/ltable.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/ltm.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lundump.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lvm.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lzio.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/ltests.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lauxlib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lbaselib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/ldblib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/liolib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lmathlib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/loslib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/ltablib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lstrlib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lutf8lib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/loadlib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/lcorolib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/linit.c
)
target_link_libraries(lua PUBLIC ${WR_RUNTIME_LIBS})
target_include_directories(lua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua)