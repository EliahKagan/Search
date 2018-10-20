cmake_minimum_required(VERSION 3.0.0)
project(Search VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

add_executable(Search
    search.cpp
    Lnode.h Lnode.cpp
    loops.h loops.cpp
    Pool.cpp Pool.h
    Pool-test.cpp Pool-test.h
)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -Wno-padded -Wno-unused-member-function -Wno-exit-time-destructors -Wno-sign-conversion")
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
