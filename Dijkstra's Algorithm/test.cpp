#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include "Graph.hpp"

int main(int argc, char const *argv[])
{
    /* code */
    Graph g;
    std::vector<std::string> vertices1 = { "1", "2", "3", "4", "5", "6" };
    std::vector<std::tuple<std::string, std::string, unsigned long>> edges1 = { {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14}, {"2", "3", 10}, {"2", "4", 15}, {"3", "4", 11}, {"3", "6", 2}, {"4", "5", 6}, {"5", "6", 9} };

    // std::vector<std::string> vertices1 = { "1", "2"};
    // std::vector<std::tuple<std::string, std::string, unsigned long>> edges1 = { {"1", "2", 7} };

    for (const auto label : vertices1) g.addVertex(label);
    for (const auto &tuple : edges1) g.addEdge(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple));

    std::vector<std::string> path;
    g.shortestPath("1", "5", path); // == 20
    g.print();
    std::cout << "---" << std::endl;
    // g.removeVertex("2");
    g.removeEdge("1", "2");
    g.print();
    // g.shortestPath("1", "5", path); // = { "1", "3", "6", "5" }

    return 0;
}