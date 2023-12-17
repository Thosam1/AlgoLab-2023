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
        "W3 - BGL - Graphs/ImportantBridges.cpp"
        "W3 - BGL - Graphs/Ant Challenge.cpp"
        "W6 - BGL - Flow Networks/London.cpp"
        base_template.cpp
        template_base.cpp
        "W7 - CGAL - Proximity Structures/Bistro.cpp"
        "W7 - CGAL - Proximity Structures/H1N1.cpp"
        "W6 - BGL - Flow Networks/Tiles.cpp"
        "W6 - BGL - Flow Networks/CoinTossingTournament.cpp"
        "W6 - BGL - Flow Networks/Knights.cpp"
        "W4 - Geometry Algebra/First Hit.cpp"
        "W4 - Geometry Algebra/Hit.cpp"
        "W4 - Geometry Algebra/Antenna.cpp"
        "W7 - CGAL - Proximity Structures/Golden Eye.cpp"
        "W8 - Linear Programming/Maximize it!.cpp"
        "W8 - Linear Programming/Suez.cpp"
        "W8 - Linear Programming/Inball.cpp"
        "W8 - Linear Programming/Diet.cpp"
        "W9 - Advanced Flows/Canteen.cpp"
        "W9 - Advanced Flows/Placing Knights.cpp"
        "W9 - Advanced Flows/Real Estate Market.cpp"
        "W9 - Advanced Flows/Algocoon.cpp"
)

