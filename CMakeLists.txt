cmake_minimum_required (VERSION 2.6)
project (Tutorial)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
set(CMAKE_BUILD_TYPE Debug)


# The version number.
set (convolve 1)

set (SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set (BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include usr/include usr/local/lib /usr/local/include )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)

include_directories ( ${INCLUDE_DIR} )

add_executable(main_exec src/main.c)
set_target_properties(main_exec PROPERTIES CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin)
