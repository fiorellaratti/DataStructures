#ifndef DIJKSTRASTRUCT_H
#define DIJKSTRASTRUCT_H

#include <vector>
#include "Vertex.hpp"

class DijkstraStruct {
    private:
        unsigned long shortestPath;
        Vertex* prevVert;
    public:
        DijkstraStruct(unsigned long shortestPath, Vertex* prevVert);
    friend class Graph;
};

#endif