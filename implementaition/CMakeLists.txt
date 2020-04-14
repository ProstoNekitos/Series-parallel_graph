cmake_minimum_required(VERSION 3.14)
project(SPgraph)

set(CMAKE_CXX_STANDARD 17)

set(GRAPH SPGraph/SPGraph.h SPGraph/SPiterator.h SPGraph/SPException.h)

set(SHAPES shapes/Shape.cpp shapes/Shape.h
        shapes/Circle.cpp shapes/Circle.h
        shapes/Ellipse.cpp shapes/Ellipse.h
        shapes/Helix.cpp shapes/Helix.h
        shapes/Text.cpp shapes/Text.h
        shapes/TextInEllipse.cpp shapes/TextInEllipse.h)

include_directories(shapes)
add_executable(graph main.cpp ${GRAPH} ${SHAPES})
add_executable(containter_only containers_only.cpp ${SHAPES})