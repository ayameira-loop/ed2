#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <limits>
#define NINF std::numeric_limits<int>::lowest()

// Graph class
class Graph {
private:
    int V;                    // Number of vertices in the graph
    std::vector<float> weigths;  // Vertices
    std::vector<std::string> vertices;  // Vertices
    std::vector<std::vector<int>> adj;  // Adjacency list

public:
    // Constructor
    Graph(int V) : V(V), weights(V), vertices(V), adj(V) {}

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
    
    void topologicalSortUtil(int v, std::vector<bool>& visited, std::stack<int>& stack) {
        // Mark the current node as visited
        visited[v] = true;
    
        // Recur for all the vertices adjacent to this vertex
        for (int adjVertex : adj[v]) {
            if (!visited[adjVertex])
                topologicalSortUtil(adjVertex, visited, stack);
        }
    
        // Push current vertex to stack which stores topological
        stack.push(v);
    }
void longestPath(int s)
{
    std::stack<int> stack;
    std::vector<bool> visited(V, false);
    int dist[V];
   
   
    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, stack);
   
    // Initialize distances to all vertices as infinite and
    // distance to source as 0
    for (int i = 0; i < V; i++)
        dist[i] = NINF;
    dist[s] = 0;
    // Process vertices in topological order
    while (stack.empty() == false) {
        // Get the next vertex from topological order
        int u = stack.top();
        stack.pop();
   
        // Update distances of all adjacent vertices
        if (dist[u] != NINF) {
            for (int adjVertex : adj[u]) {
             
                if (dist[adjVertex] < dist[u] + weights[adjVertex])
                    dist[adjVertex] = dist[u] + weigths[adjVertex];
            }
        }
    }
   
    // Print the calculated longest distances
    for (int i = 0; i < V; i++)
        (dist[i] == NINF) ? cout << "INF " : cout << dist[i] << " ";
     
    delete [] visited;
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

int main() {
    // Create a graph with 5 vertices
    int V=7;
    Graph graph(V);

    // Set values for vertices
    graph.setVertexValue(0, "0");
    graph.setVertexValue(1, "1");
    graph.setVertexValue(2, "2");
    graph.setVertexValue(3, "3");
    graph.setVertexValue(4, "4");
    graph.setVertexValue(5, "5");
    graph.setVertexValue(6, "6");

    // Add edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 3);
    graph.addEdge(4, 5);
    graph.addEdge(1, 6);
    graph.addEdge(6, 5);
    graph.addEdge(3, 2);
    //graph.addEdge(1, 2);
    //graph.addEdge(1, 3);


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
    std::stack<int> sortedStack;
    std::vector<bool> visited(V, false);

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            graph.topologicalSortUtil(i, visited, sortedStack);
        }
    }

    // Print the topological order
    std::cout << "Topological order: ";
    while (!sortedStack.empty()) {
        std::cout << sortedStack.top() << " ";
        sortedStack.pop();
    }
    std::cout << std::endl;

    return 0;
}
