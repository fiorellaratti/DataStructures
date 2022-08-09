#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include "Vertex.hpp"

class Vertex;

class Edge {
    private:
    public:
        Edge(unsigned long weight, Vertex* vertPrev, Vertex* vertNext);
        unsigned long weight;
        Vertex* vertPrev;
        Vertex* vertNext;
        void print();
    friend class Graph;
};

#endif