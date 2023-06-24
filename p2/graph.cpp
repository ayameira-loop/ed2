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
        std::cout << "visitei " << src << std::endl;
        std::cout << "quero chegar em " << dest << std::endl;
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
    Graph graph(5);

    // Add edges
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    std::cout << "Fonte?" << std::endl;
    std::cout << graph.achaFonte() << std::endl;

    std::vector<int> seq;
    seq.push_back(0);
    seq.push_back(1);
    seq.push_back(3);
    seq.push_back(2);
    seq.push_back(4);
    
    //std::cout << "Caminho: " << std::endl;
    //std::cout << graph.temCaminho(2, 0) << std::endl;

    //std::vector<bool> visited(graph.size(), false); 
    //std::vector<int> accessible(graph.size(), -1);
    //graph.dfs(3, visited, accessible);

    std::cout << "K Caminho: " << std::endl;
    std::cout << graph.temkcaminho(0, 2, 1) << std::endl;
    
    // Print the graph
    graph.printGraph();

    return 0;
}

