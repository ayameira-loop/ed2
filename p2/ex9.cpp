#include <iostream>
#include <vector>

class Graph {

private: 
    int V;
    int** adj;

public:

    Graph(int numberOfVertices) {
        V = numberOfVertices;
        adj = new int*[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new int[V];
            for (int j = 0; j < V; j++)
                adj[i][j] = 0;
        }
    }
    ~Graph() {
        for (int i = 0; i < V; i++) {
            delete[] adj[i];
        }
        delete[] adj;
    }
    void addEdge(int u, int v) {
        adj[u][v] = 1;
    }

    void removeEdge(int u, int v) {
        adj[u][v] = 0;
    }

    void dfs(int u, std::vector<bool> &visited, std::vector<int> &starts, std::vector<int> &ends, int &time) {
        visited[u] = true;
        std::cout << "comeca a explorar " << u << " no tempo " << time << std::endl;
        starts[u] = time++;
        for (int v = 0; v < V; v++) {
            if (adj[u][v]) {
                if (!visited[v]) {
                    dfs(v, visited, starts, ends, time);
                }
            }
        }
        std::cout << "termina de explorar " << u << " no tempo " << time << std::endl;
        ends[u] = time;
    }

    void printGraph() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++)
                std::cout << adj[i][j] << " ";
            std::cout << std::endl;
        }
    }

    int size() {
        return V;
    }
};

int main() {
    int V = 15;
    Graph G(V);

    // Add edges
    G.addEdge(1, 2);
    G.addEdge(1, 8);
    G.addEdge(1, 9);
    G.addEdge(1, 11);
    G.addEdge(2, 8);
    G.addEdge(2, 9);
    G.addEdge(8, 3);
    G.addEdge(3, 4);
    G.addEdge(3, 12);
    G.addEdge(3, 6);
    G.addEdge(4, 5);
    G.addEdge(5, 12);
    G.addEdge(12, 4);
    G.addEdge(12, 3);
    G.addEdge(6, 2);
    G.addEdge(6, 9);
    G.addEdge(6, 7);
    G.addEdge(14, 5);
    G.addEdge(14, 13);
    G.addEdge(13, 14);
    G.addEdge(13, 6);
    G.addEdge(13, 7);
    G.addEdge(7, 9);
    G.addEdge(9, 10);
    G.addEdge(9, 11);
    G.addEdge(10, 9);
    G.addEdge(10, 7);
    G.addEdge(11, 10);

    std::vector<bool> visited(V, false);
    std::vector<int> starts(V, -1);
    std::vector<int> ends(V, 0);
    int time = 0;
    G.dfs(1, visited, starts, ends, time);

    for (size_t i = 0; i < V; i++)
        std::cout << i << " starts at " << starts[i] << std::endl;

    for (size_t i = 0; i < V; i++)
        std::cout << i << " ends at " << ends[i] << std::endl;
    
    // Print the graph

    return 0;
}

