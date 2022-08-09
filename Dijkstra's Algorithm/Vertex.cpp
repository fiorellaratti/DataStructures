#include <iostream>
#include "Vertex.hpp"

Vertex::Vertex(std::string label) {
    this->label = label;
}

// Destructor
Vertex::~Vertex() {
    std::vector<Edge*>::iterator it;
    for (it = edges.begin(); it != edges.end(); ++it) {
        delete *it;
    }
}

std::string Vertex::getLabel() {
    return label;
}

void Vertex::addEdge(Edge* e) {
    // std::cout << "--- Vertex::addEdge ---" << std::endl;
    // std::cout << e << std::endl;
    edges.push_back(e);
    // e->print();
    // std::cout << edges.size() << std::endl;
    // std::cout << "--- end Vertex::addEdge ---" << std::endl;
}

void Vertex::removeEdge(Edge* e) {
    std::vector<Edge*>::iterator it;
    for (it = edges.begin(); it != edges.end(); ++it) {
        if(*it == e) {
            edges.erase(it);
            return;
        }
    }
    // TO-DO Throw Exception
}

std::vector<Edge*> Vertex::getEdges() {
    return edges;
};

std::string Vertex::print() {
    std::string str = "";
    std::vector<Edge*>::iterator it;
    for (it = edges.begin(); it != edges.end(); ++it) {
        if((*it)->vertPrev == this) {
            str += (*it)->vertNext->getLabel() + " ";
            continue;
        }
        if((*it)->vertNext == this) {
            str += (*it)->vertPrev->getLabel() + " ";
            continue;
        }
    }
    return str;
}
