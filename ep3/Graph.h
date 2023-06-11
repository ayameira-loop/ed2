#include <iostream>
#include <vector>
#include <stack>
#include <string>

class Graph {
private:
    int V;                    // Number of vertices in the graph
    std::vector<std::string> vertices;  // Vertices
    std::vector<std::vector<int>> adj;  // Adjacency list

public:
    // Constructor
    Graph(int V) : V(V), vertices(V), adj(V) {}

    void setVertexValue(int vertex, const std::string& value) {
        vertices[vertex] = value;
    }

    void addEdge(int src, int dest) {
        adj[src].push_back(dest);
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
    
    void longestPathUtil(int src, std::vector<int>& path, std::vector<bool>& visited, std::vector<int>& maxPath, int& maxDistance) {
        visited[src] = true;
        path.push_back(src);

        if (path.size()-1 > maxDistance) {
            maxPath = path;
            maxDistance = path.size()-1;
        }

        for (int neighbor : adj[src]) {
            if (!visited[neighbor])
                longestPathUtil(neighbor, path, visited, maxPath, maxDistance);
        }

        path.pop_back();
        visited[src] = false;
    }

    void findLongestPath() {
        std::vector<bool> visited(V, false);
        std::vector<int> path, maxPath;
        int maxDistance = 0;

        for (int i = 0; i < V; ++i) {
            if (!visited[i])
                longestPathUtil(i, path, visited, maxPath, maxDistance);
        }

        std::cout << "Longest Path: ";
        for (int vertex : maxPath)
            std::cout << vertices[vertex] << " ";
        std::cout << std::endl;
        std::cout << "Max Distance: " << maxDistance << std::endl;
    }

    void printGraph() {
        for (int i = 0; i < V; ++i) {
            std::cout << "Vertex " << i << " (" << vertices[i] << "): ";
            for (int j : adj[i]) {
                std::cout << vertices[j] << " ";
            }
            std::cout << std::endl;
        }
    }
};