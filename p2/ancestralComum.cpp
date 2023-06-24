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

    int achaFonte() {
        for (int j = 0; j < V; j++) {
            bool temEntradaNula = true;
            for (int i = 0; i < V; i++) {
                if (adj[i][j]) {
                    temEntradaNula = false;
                }
            }
            if (temEntradaNula)
                return j;
        }
        return -1;
    }

    bool testaCaminho(std::vector<int> seq) {
        int prev = seq[0];
        seq.erase(seq.begin());
        for (int i : seq) {
            if (!adj[prev][i]) {
                return false;
            }
            prev = i;
        }
        return true;
    }

    void dfs(int u, std::vector<bool> &visited, std::vector<int> &accessible) {
        visited[u] = true;
        for (int v = 0; v < V; v++) {
            if (adj[u][v]) {
                if (!visited[v]) {
                    dfs(v, visited, accessible);
                }
            }
        }
        std::cout << u << std::endl;
        accessible.push_back(u);
    }

    void temCaminhoR(int src, int dest, std::vector<int> visited, bool &achei) {
        visited[src] = true;
        if (src == dest)    achei = true;
        for (int i = 0; i < V; i++) {
            if (adj[src][i]) {
                if (!visited[i]) {
                    temCaminhoR(i, dest, visited, achei);
                }
            }
        }
    }
    bool temCaminho(int u, int v) {
        std::vector<int> visited(V, 0);
        bool achei = false;
        temCaminhoR(u, v, visited, achei);
        return achei;
    }

    bool temkcaminho(int u, int v, int k) {
        std::vector<int> visited(V, 0);
        bool achei = false;
        kcaminhoR(u, v, k, visited, achei);
        return achei;
    }
    void kcaminhoR(int src, int dest, int k, std::vector<int> visited, bool &achei) {
        if (k == 0)  return;
        if (src == dest) {
            achei = true; 
            return;
        }
        visited[src] = 1;
        for (int i = 0; i < V; i++) {
            if (adj[src][i] && !visited[i])
                kcaminhoR(i, dest, k-1, visited, achei);
        }
    }

    bool ancestralComum(int u, int v, int w) {
        return temCaminho(w, u) && temCaminho(w, v);
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
    Graph graph(7);

    // Add edges
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(2, 4);
    graph.addEdge(2, 3);
    graph.addEdge(5, 6);
    graph.addEdge(6, 3);

  //       0        5
  //      / \      /
  //     1   2    6
  //         / \ /
  //        4   3
    std::cout << "Caminho 5-3: " << std::endl;
    std::cout << graph.temCaminho(5, 3) << std::endl;

    std::cout << "Caminho 0-3: " << std::endl;
    std::cout << graph.temCaminho(0, 3) << std::endl;

    std::cout << "Caminho 0-2: " << std::endl;
    std::cout << graph.temCaminho(0, 2) << std::endl;
    
    std::cout << "Ancestral comum 0 de 2 e 3: " << std::endl;
    std::cout << graph.ancestralComum(2, 3, 0) << std::endl;

    // Print the graph
    graph.printGraph();

    return 0;
}

