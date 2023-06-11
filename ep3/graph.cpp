#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <limits>
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

    void DFS(int v, std::vector<int>& low, std::vector<int>& disc, std::stack<int>& stack, std::vector<bool>& inStack, int& time) {
        disc[v] = low[v] = ++time;
        stack.push(v);
        inStack[v] = true;

        for (int adjVertex : adj[v]) {
            if (disc[adjVertex] == -1) {
                DFS(adjVertex, low, disc, stack, inStack, time);
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
                DFS(i, low, disc, stack, inStack, time);
            }
        }
    }
    
    void highestWeightPath(int src, std::vector<int>& path, std::vector<bool>& visited, std::vector<int>& maxPath, int& maxWeight) {
        visited[src] = true;
        path.push_back(src);

        if (calculatePathWeight(path) > maxWeight) {
            maxPath = path;
            maxWeight = calculatePathWeight(path);
        }

        for (int neighbor : adj[src]) {
            if (!visited[neighbor])
                highestWeightPath(neighbor, path, visited, maxPath, maxWeight);
        }

        path.pop_back();
        visited[src] = false;
    }

    int calculatePathWeight(std::vector<int> path) {
        int weight = 0;
        for (int i = 0; i < path.size() - 1; ++i)
            weight += weights[path[i]][path[i+1]];
        return weight;
    }

    void findHighestWeightPath() {
        std::vector<bool> visited(V, false);
        std::vector<int> path, maxPath;
        int maxWeight = NINF;

        for (int i = 0; i < V; ++i) {
            if (!visited[i])
                highestWeightPath(i, path, visited, maxPath, maxWeight);
        }

        std::cout << "Highest Weight Path: ";
        for (int vertex : maxPath)
            std::cout << vertices[vertex] << " ";
        std::cout << std::endl;
        std::cout << "Total Weight: " << maxWeight << std::endl;
    }

    void topologicalSortUtil(int v, std::vector<bool>& visited, std::stack<int>& stack) {
        visited[v] = true;
        for (int adjVertex : adj[v]) {
            if (!visited[adjVertex])
                topologicalSortUtil(adjVertex, visited, stack);
        }
        stack.push(v);
    }

    std::vector<int> topologicalSort() {
        std::vector<bool> visited(V, false);
        std::stack<int> sortedStack;

        for (int i = 0; i < V; ++i) {
            if (!visited[i])
                topologicalSortUtil(i, visited, sortedStack);
        }

        std::vector<int> topologOrder;
        while (!sortedStack.empty()) {
            topologOrder.push_back(sortedStack.top());
            sortedStack.pop();
        }

        return topologOrder;
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
    graph.addEdge(5, 2, 1);
    graph.addEdge(5, 0, 1);
    graph.addEdge(4, 0, 1);
    graph.addEdge(4, 1, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 1, 1);

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
    for (int vertex : topOrder)
        std::cout << topOrder[vertex] << " ";
    std::cout << std::endl;

    // Print the longest path
    //graph.longestPath(0);
    graph.findHighestWeightPath();
    return 0;
}
