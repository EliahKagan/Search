cmake_minimum_required(VERSION 3.0.0)
project(Search VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

add_executable(Search
    search.cpp
    Lnode.cpp Lnode.h
    loops.cpp loops.h
    Pool.cpp Pool.h
    Pool-test.cpp Pool-test.h
    Tnode.cpp Tnode.h
    tree-test.cpp tree-test.h
    vecutil.cpp vecutil.h
)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -Wno-padded -Wno-unused-member-function -Wno-exit-time-destructors -Wno-sign-conversion -Wno-sign-compare -Wno-float-equal")
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
