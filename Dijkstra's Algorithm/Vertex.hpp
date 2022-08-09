#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <string>
#include "Edge.hpp"

class Edge;

class Vertex {
    private:
        std::string label;
        std::vector<Edge*> edges;
    public:
        Vertex(std::string label);
        ~Vertex();
        std::string getLabel();
        void addEdge(Edge* e);
        void removeEdge(Edge* e);
        std::vector<Edge*> getEdges();
        std::string print();
    friend class Graph;
};

#endif