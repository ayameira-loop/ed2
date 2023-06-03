#include <iostream>
#include <vector>
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
        adj[dest].push_back(src);
    }
    bool isCyclicDFSUtil(int v, std::vector<bool>& visited, int parent) {
        visited[v] = true;

        for (int adjVertex : adj[v]) {
            if (!visited[adjVertex]) {
                if (isCyclicDFSUtil(adjVertex, visited, v)) {
                    return true;
                }
            } else if (adjVertex != parent) {
                return true;
            }
        }

        return false;
    }

    bool isCyclic() {
        std::vector<bool> visited(V, false);

        for (int i = 0; i < V; ++i) {
            if (!visited[i] && isCyclicDFSUtil(i, visited, -1)) {
                return true;
            }
        }

        return false;
    }

    void removeEdge(int src, int dest) {
        for (auto it = adj[src].begin(); it != adj[src].end(); ++it) {
            if (*it == dest) {
                adj[src].erase(it);
                break;
            }
        }
        for (auto it = adj[dest].begin(); it != adj[dest].end(); ++it) {
            if (*it == src) {
                adj[dest].erase(it);
                break;
            }
        }
    }

    void removeCycleDFS(int v, std::vector<bool>& visited, int parent) {
        visited[v] = true;

        for (int adjVertex : adj[v]) {
            if (!visited[adjVertex]) {
                removeCycleDFS(adjVertex, visited, v);
            } else if (adjVertex != parent) {
                removeEdge(v, adjVertex);
            }
        }
    }

    void removeCycle() {
        std::vector<bool> visited(V, false);

        for (int i = 0; i < V; ++i) {
            if (!visited[i] && isCyclicDFSUtil(i, visited, -1)) {
                std::fill(visited.begin(), visited.end(), false);
                removeCycleDFS(i, visited, -1);
                break;
            }
        }
    }

    void DFS(int v, std::vector<bool>& visited, int& farthestVertex, int& maxDistance, int distance) {
        visited[v] = true;

        if (distance > maxDistance) {
            maxDistance = distance;
            farthestVertex = v;
        }

        for (int adjVertex : adj[v]) {
            if (!visited[adjVertex]) {
                DFS(adjVertex, visited, farthestVertex, maxDistance, distance + 1);
            }
        }
    }

    int findFarthestVertex(int startVertex) {
        std::vector<bool> visited(V, false);
        int farthestVertex = startVertex;
        int maxDistance = 0;

        DFS(startVertex, visited, farthestVertex, maxDistance, 0);

        return farthestVertex;
    }

    int printLongestPath() {
        int u = 0;
        int v = findFarthestVertex(u);
        int w = findFarthestVertex(v);
        printPath(v, w);

    }

    void printPath(int u, int v) {
        std::vector<int> path;
        std::vector<bool> visited(V, false);
        getPathDFS(u, v, visited, path);
        for (int i = 0; i < path.size(); ++i) {
            std::cout << vertices[path[i]];
            if (i != path.size() - 1) {
                std::cout << " -> ";
            }
        }
    }
    bool getPathDFS(int u, int v, std::vector<bool>& visited, std::vector<int>& path) {
        visited[u] = true;
        path.push_back(u);

        if (u == v) {
            return true;
        }

        for (int adjVertex : adj[u]) {
            if (!visited[adjVertex]) {
                if (getPathDFS(adjVertex, v, visited, path)) {
                    return true;
                }
            }
        }

        path.pop_back();
        return false;
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