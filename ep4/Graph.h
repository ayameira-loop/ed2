#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <limits>
#include <algorithm>

class Graph {
private:
    int V;
    std::vector<char> vertices;
    std::vector<std::vector<int>> adj;

public:
    Graph(int V);
    void setVertexValue(int vertex, char value);
    void addEdge(int src, int dest);
    void dfs(int vertex, std::vector<bool>& marked);
    void printGraph();
    int size();
};

#endif
