#include <iostream>
#include <string>
#include <map>
#include "Graph.hpp"
#include "Edge.hpp"
#include "DijkstraStruct.hpp"
#include <algorithm>
#include <limits>

using namespace std;

Graph::Graph() {
    std::vector<Vertex*> vertices;
}

void Graph::addVertex(std::string label) {
    Vertex* tempVert = new Vertex(label);
    vertices.push_back(tempVert);
    // std::cout << vertices.size() << std::endl;
}

void Graph::removeVertex(std::string label) {
    // Find vertexByLabel
    std::vector<Vertex*>::iterator vertA = getVertexByLabel(label);
    std::vector<Edge*> edges = (*vertA)->getEdges();
    std::vector<Edge*>::iterator it;
    // Iterate over every Edge and remove Edge from Vertex.edges vector
    for (it = edges.begin(); it != edges.end(); ++it) {
        if((*it)->vertPrev == *vertA) {
            (*it)->vertNext->removeEdge(*it);
            continue;
        }
        if((*it)->vertNext == *vertA) {
            (*it)->vertPrev->removeEdge(*it);
            continue;
        }
    }
    vertices.erase(vertA);
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    // std::cout << "--- addEdge ---" << std::endl;
    std::vector<Vertex*>::iterator vertPrev = getVertexByLabel(label1);
    // std::cout << *vertPrev << std::endl;
    std::vector<Vertex*>::iterator vertNext = getVertexByLabel(label2);
    // std::cout << *vertNext << std::endl;
    Edge* tempEdge = new Edge(weight, *vertPrev, *vertNext);
    // std::cout << tempEdge << std::endl;
    (*vertPrev)->addEdge(tempEdge);
    (*vertNext)->addEdge(tempEdge);
    // std::cout << "--- end addEdge ---" << std::endl;
}

void Graph::removeEdge(std::string label1, std::string label2) {
    std::vector<Vertex*>::iterator vertA = getVertexByLabel(label1);
    // std::cout << *vertA << std::endl;
    std::vector<Vertex*>::iterator vertB = getVertexByLabel(label2);
    // std::cout << *vertB << std::endl;
    Edge* edge = getEdgeByVertex(*vertA, *vertB);
    // std::cout << "edge: " << edge << std::endl;
    // edge->print();

    (*vertA)->removeEdge(edge);
    (*vertB)->removeEdge(edge);
    delete edge;
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) 
{
    std::map<std::string, unsigned long> shortestDistFromStart; // Will store the known distances of vertices from start
    std::map<std::string, std::string> previousVertex; // Will store the previous vertex in traversal (used to update path)
    std::vector<std::string> visited; // To keep track of visted vertices in traversal
    std::vector<std::string> unvisited; // To keep track of unvisted vertices in traversal

    // Set the shortest distance from start of the startLabel vertex to 0 and that of the other vertices to "infinity"
    for (auto it = adj.begin(); it != adj.end(); ++it)
    {
        if (it->first == startLabel)
        {
            shortestDistFromStart.insert(std::pair<std::string, unsigned long>(it->first, 0)); // Shortest distance from start to itself is 0
        }
        else
        {
            shortestDistFromStart.insert(std::pair<std::string, unsigned long>(it->first, std::numeric_limits<unsigned long>::max())); // Shortest distance from start to everything else is initially infinity
        }

        unvisited.push_back(it->first); // Add all vertices to unvisited vector
    }

    
    
    std::string prev = startLabel; // Begin traversal by visiting the startLabel vertex

    while (!unvisited.empty()) // Check to make sure there are unvisited vertices to look at
    {
        auto it = adj.find(prev); // Iterator to the Vertex being visited
        unsigned long dist = shortestDistFromStart[it->first]; // Current shortest distance from start of vertex being visited

        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) // Will search all the adjacent vertices to the current Vertex being visited
        {
            if (std::count(unvisited.begin(), unvisited.end(), it2->first)) // Check to make sure adjacent vertex being examined is still unvisited
            {
                unsigned long newDist = dist + it2->second;
                if (newDist < shortestDistFromStart[it2->first]) // Check if new distance is less than known distance
                {
                    shortestDistFromStart[it2->first] = newDist; // Update known distance
                    previousVertex[it2->first] = it->first; // Update previous vertex
                }
            }
        }
        

        auto unvisitedIt = std::find(unvisited.begin(), unvisited.end(), it->first); // Iterator that will be used to remove the vertex being currently visited from the unvisited vector
        unvisited.erase(unvisitedIt);
        visited.push_back(it->first);
        
        auto firstUnvisitedIt = unvisited.begin(); // When choosing the next vertex, it is important that it has been unvisited
    
        unsigned long min = shortestDistFromStart.find(*firstUnvisitedIt)->second; // Get the shortest distance from start of the first unvisited vertex
        prev = shortestDistFromStart.find(*firstUnvisitedIt)->first;
        for (auto distIt = shortestDistFromStart.begin(); distIt != shortestDistFromStart.end(); ++distIt)
        {
            if (std::count(unvisited.begin(), unvisited.end(), distIt->first)) // Check that vertex has been unvisited
            {
                // The next vertex visited should be one who has the shortest distance from start of any other unvisited vertex
                if (distIt->second < min)
                {
                    min = distIt->second;
                    prev = distIt->first;
                }
            }
        }
    }

    std::string currLabel = endLabel;
    path.insert(path.begin(), currLabel); // Add the end label to the path

    do
    {
        currLabel = previousVertex.find(currLabel)->second; // Find vertices that had to be visited to get the the current vertex, inserting them to the front of the path
        path.insert(path.begin(), currLabel);
    } while (currLabel != startLabel);

    return shortestDistFromStart[endLabel]; // The distance will be stored in the shortestDistFromStart map with a key corresponding to the endLabel vertex
}

std::vector<Vertex*>::iterator Graph::getVertexByLabel(std::string label) {
    std::vector<Vertex*>::iterator it;
    for (it = vertices.begin(); it != vertices.end(); ++it) {
        if((*it)->getLabel() == label) {
            return it;
        }
    }
    // TO-DO Throw Exception
    return it;
}

Edge* Graph::getEdgeByVertex(Vertex* vertA, Vertex* vertB) {
    // std::cout << "vertB: " << vertB << std::endl;
    std::vector<Edge*> edges = vertA->getEdges();
    std::vector<Edge*>::iterator it;
    for (it = edges.begin(); it != edges.end(); ++it) {
        // std::cout << "(*it)->vertPrev: " << (*it)->vertPrev << ", (*it)->vertNext:" << (*it)->vertNext << std::endl;
        if((*it)->vertPrev == vertB || (*it)->vertNext == vertB) {
            // std::cout << "TRUE" << std::endl;
            // std::cout << "it: " << *it << std::endl;
            return *it;
        }
    }
    // TO-DO Throw Exception
    return *it;
}

void Graph::print() {
    for (std::vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        //std::cout << "label:" << (*it)->getLabel() << ", Connected to: " << (*it)->print() << std::endl;
    }
}