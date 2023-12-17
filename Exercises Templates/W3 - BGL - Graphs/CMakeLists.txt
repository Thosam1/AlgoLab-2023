cmake_minimum_required(VERSION 3.26)
project(Exercises_Templates)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT /opt/homebrew/bin/brew)
set(BOOST_INCLUDEDIR /opt/homebrew/bin/brew)
set(BOOST_LIBRARYDIR /opt/homebrew/bin/brew)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_executable(Exercises_Templates main.cpp
        yolo.cpp
        "BGL examples/bgl_intro_connected_compontents.cpp"
        "BGL examples/bgl_intro_dijkstra.cpp"
        "BGL examples/bgl_intro_edmonds.cpp"
        "BGL examples/bgl_intro_init.cpp"
        "BGL examples/bgl_intro_kruskal.cpp"
        "BGL examples/bgl_intro_universal_fast.cpp"
        "BGL examples/bgl_intro_universal_slow.cpp"
        stdc++.h
        "W3 - BGL - Graphs/FirstStepsWithBGL.cpp"
)

