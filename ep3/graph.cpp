#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <limits>
#include <algorithm>

#define NINF std::numeric_limits<int>::lowest()

// Graph class
class Graph {
private:
    int V;                    // Number of vertices in the graph
    std::vector<std::vector<int>> weights;  // Weights
    std::vector<std::string> vertices;  // Vertices
    std::vector<std::vector<int>> adj;  // Adjacency list

public:
    // Constructor
    Graph(int V) : V(V), weights(V, std::vector<int>(V, 0)), vertices(V), adj(V) {}

    void setVertexValue(int vertex, const std::string& value) {
        vertices[vertex] = value;
    }

    void addEdge(int src, int dest, int weight) {
        adj[src].push_back(dest);
        weights[src][dest] = weight;
    }

    bool isCyclicUtil(int v, std::vector<bool>& visited, std::vector<bool>& recursionStack) {
        visited[v] = true;
        recursionStack[v] = true;

        for (int adjVertex : adj[v]) {
            if (!visited[adjVertex]) {
                if (isCyclicUtil(adjVertex, visited, recursionStack)) {
                    return true;
                }
            } else if (recursionStack[adjVertex]) {
                return true;
            }
        }

        recursionStack[v] = false;
        return false;
    }

    bool isCyclic() {
        std::vector<bool> visited(V, false);
        std::vector<bool> recursionStack(V, false);

        for (int i = 0; i < V; ++i) {
            if (!visited[i] && isCyclicUtil(i, visited, recursionStack)) {
                return true;
            }
        }

        return false;
    }

    void DFS_Cycle(int v, std::vector<int>& low, std::vector<int>& disc, std::stack<int>& stack, std::vector<bool>& inStack, int& time) {
        disc[v] = low[v] = ++time;
        stack.push(v);
        inStack[v] = true;

        for (int adjVertex : adj[v]) {
            if (disc[adjVertex] == -1) {
                DFS_Cycle(adjVertex, low, disc, stack, inStack, time);
                low[v] = std::min(low[v], low[adjVertex]);
            } else if (inStack[adjVertex]) {
                low[v] = std::min(low[v], disc[adjVertex]);
            }
        }

        if (low[v] == disc[v]) {
            // Remove the cycle
            while (stack.top() != v) {
                int u = stack.top();
                stack.pop();
                inStack[u] = false;

                // Remove edge u -> v
                for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
                    if (*it == v) {
                        adj[u].erase(it);
                        break;
                    }
                }
            }

            // Remove v from stack and inStack
            stack.pop();
            inStack[v] = false;
        }
    }

    void makeAcyclic() {
        std::vector<int> low(V, -1);         // Low-link values for vertices
        std::vector<int> disc(V, -1);        // Discovery time of vertices
        std::vector<bool> inStack(V, false); // Tracks vertices in the recursion stack
        std::stack<int> stack;
        int time = 0;

        for (int i = 0; i < V; ++i) {
            if (disc[i] == -1) {
                DFS_Cycle(i, low, disc, stack, inStack, time);
            }
        }
    }

    void dfs(int v, std::vector<bool>& visited, std::vector<int>& visitedNodes) {
        visited[v] = true;

        for (int u : adj[v]) {
            if (!visited[u]) {
                dfs(u, visited, visitedNodes);
            }
        }
        visitedNodes.push_back(v);
        return;
    }

    std::vector<int> topologicalSort() {
        std::vector<int> ordering(V, 0);
        std::vector<bool> visited(V, false);
        int i = V - 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v]) {
                std::vector<int> visitedNodes;
                dfs(v, visited, visitedNodes);
                for (int nodeId : visitedNodes) {
                    ordering[i] = nodeId;
                    i--;
                }
            }
        }
        return ordering;
    }

    std::vector<int> longestPath() {
        std::vector<int> topOrder = topologicalSort();
        std::vector<int> prev(V, -1);
        std::vector<int> dist(V, NINF);
        int maxWeight = 0;
        int lastVertex = -1;

        dist[topOrder[0]] = 0;

        // Process vertices in topological order
        int t = 0;
        while (t < V) {
            int u = topOrder[t];
            // Update distances of all adjacent vertices
            if (dist[u] != NINF) {
                for (int adjVertex : adj[u]) {
                    int newDist = dist[u] + weights[u][adjVertex];
                    if (newDist > dist[adjVertex]) {
                        dist[adjVertex] = dist[u] + weights[u][adjVertex];
                        prev[adjVertex] = u;
                    }
                }
            }
            if (dist[u] > maxWeight) {
                maxWeight = dist[u];
                lastVertex = u;
            }
            t++;
        }
        // Reconstruct the highest weight path
        std::vector<int> path;
        while (lastVertex != -1) {
            path.push_back(lastVertex);
            lastVertex = prev[lastVertex];
        }
        std::reverse(path.begin(), path.end());
        return path;
    }
    
    void printGraph() {
        for (int i = 0; i < V; ++i) {
            std::cout << "Vertex " << i << " (" << vertices[i] << "): ";
            for (int j : adj[i]) {
                std::cout << vertices[j] << " (w: " << weights[i][j] << ") ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    // Create a graph with 5 vertices
    int V = 6;
    Graph graph(V);

    // Set values for vertices
    graph.setVertexValue(0, "0");
    graph.setVertexValue(1, "1");
    graph.setVertexValue(2, "2");
    graph.setVertexValue(3, "3");
    graph.setVertexValue(4, "4");
    graph.setVertexValue(5, "5");

    // Add edges to the graph
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 3, 1);
    graph.addEdge(3, 4, 1);
    graph.addEdge(3, 5, 1);
    graph.addEdge(1, 4, 6);
    graph.addEdge(5, 2, 1);

    // Is it cyclic?
    std::cout << "Cycle?" << std::endl;
    std::cout << graph.isCyclic() << std::endl;
    graph.printGraph();

    if (graph.isCyclic()) {
        graph.makeAcyclic();
        std::cout << "Cycle?" << std::endl;
        std::cout << graph.isCyclic() << std::endl;
        graph.printGraph();
    }

    // Perform topological sorting
    std::vector<int> topOrder = graph.topologicalSort();

    // Print the topological order
    std::cout << "Topological order: " << std::endl;
    for (int i = 0; i < topOrder.size(); i++)
        std::cout << topOrder[i] << " ";
    std::cout << std::endl;

    // Print the longest path
    //graph.longestPath(0);
    std::cout << "Max weight path: " << std::endl;
    std::vector<int> path = graph.longestPath();
    for (int i = 0; i < path.size(); i++)
        std::cout << path[i] << " ";    
    return 0;
}
