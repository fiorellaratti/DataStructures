#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include "Vertex.hpp"

class Graph: virtual public GraphBase {
    public:
        Graph();
        void addVertex(std::string label); // Done
        void removeVertex(std::string label); // Done
        void addEdge(std::string label1, std::string label2, unsigned long weight); // Done
        void removeEdge(std::string label1, std::string label2); // Done
        unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path); //TO-DO
        void print(); // Done
    private:
        std::vector<Vertex*> vertices;
        std::vector<Vertex*>::iterator getVertexByLabel(std::string label); // Done
        Edge* getEdgeByVertex(Vertex* vertA, Vertex* vertB); // Done
        std::map<std::string, std::map<std::string, unsigned long> > adj;
};

#endif