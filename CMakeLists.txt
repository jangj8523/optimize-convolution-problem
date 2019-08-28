cmake_minimum_required (VERSION 2.6)
project (Tutorial)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")


# The version number.
set (convolve 1)

set (SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set (BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include usr/include usr/local/lib /usr/local/include )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

include_directories ( ${INCLUDE_DIR} )
add_library( multithread SHARED src/thread_pool.c)
find_package (Threads)

TARGET_LINK_LIBRARIES(multithread ${CMAKE_THREAD_LIBS_INIT})

add_executable(main_exec src/main.c)
# find_library(multithread_lib multithread HINTS build/libmultithread.so)

TARGET_LINK_LIBRARIES(main_exec multithread)
set_target_properties(main_exec PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../build)
