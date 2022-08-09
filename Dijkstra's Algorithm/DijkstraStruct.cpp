#include "DijkstraStruct.hpp"

DijkstraStruct::DijkstraStruct(unsigned long shortestPath, Vertex* prevVert) {
    this->prevVert = prevVert;
    this->shortestPath = shortestPath;
}