#include <iostream>
#include "Edge.hpp"
#include "Vertex.hpp"

Edge::Edge(unsigned long weight, Vertex* vertPrev, Vertex* vertNext) {
    this->weight = weight;
    this->vertPrev = vertPrev;
    this->vertNext = vertNext;
}

void Edge::print() {
    std::cout << "weight: " << weight << ", vertPrev: " << vertPrev << ", vertNext: " << vertNext << std::endl;
}