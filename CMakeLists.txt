cmake_minimum_required(VERSION 3.21)
project(Peergrade_01)

set(CMAKE_CXX_STANDARD 20)

add_executable(Peergrade_01 GraphRepresentations.h GraphRepresentations/AdjacencyMatrix.cpp
        GraphRepresentations/AdjacencyList.cpp GraphRepresentations/IncidentMatrix.cpp
        GraphRepresentations/EdgesList.cpp GraphRepresentations/FoFi.cpp GraphRepresentations/MfoMfi.cpp
        Graph.h main.cpp)
