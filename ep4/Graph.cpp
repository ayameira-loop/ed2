#include "Graph.h"
#include <vector>
using namespace std;

Graph::Graph(int V) : V(V), vertices(V), adj(V) {}

void Graph::setVertexValue(int vertex, char value) {
    vertices[vertex] = value;
}

void Graph::addEdge(int src, int dest) {
    adj[src].push_back(dest);
}

void Graph::dfs(int vertex, vector<bool>&marked) {
    marked[vertex] = true;
    for (int i=0; i < adj[vertex].size(); i++) {
        if (!marked[adj[vertex][i]])
            dfs(adj[vertex][i], marked);
    }
}

void Graph::printGraph() {
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << " '" << vertices[i] << "': ";
        for (int j : adj[i]) {
            cout << j << ":" << vertices[j] << " ";
        }
        cout << endl;
    }
}

int Graph::size() {
    return V;
}
