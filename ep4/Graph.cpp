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
    int V;
    std::string regex;
    std::vector<char> vertices;
    std::vector<std::vector<int>> adj;

public:
    std::string getRegex() {
        return regex;
    }

    void dfs(int vertex, std::vector<bool>&marked) {
        marked[vertex] = true;
        for (int i=0; i < adj[vertex].size(); i++) {
            if (!marked[adj[vertex][i]])
                dfs(adj[vertex][i], marked);
        }
    }

    // Constructor
    Graph(int V, std::string regex) : regex(regex), V(V), vertices(V), adj(V) {}

    void setVertexValue(int vertex, char value) {
        vertices[vertex] = value;
    }

    void addEdge(int src, int dest) {
        adj[src].push_back(dest);
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

    void createNFA() {
        for (int i = 0; i < regex.length(); i++)
            setVertexValue(i, regex[i]);

        std::stack<int>symbols;
        std::stack<int>parenthesis;
        for (int i=0; i < regex.length(); i++) {
            int ant = i;

            if (regex[i] == '\\') {
                addEdge(i, i+1);
                i++;
            }

            else if (regex[i] == '(' || regex[i] == '|') {
                if (regex[i] == '(') parenthesis.push(i);
                symbols.push(i);
            }

            else if (regex[i] == ')') {
                while (regex[symbols.top()] != '(') {
                    int top = symbols.top();
                    symbols.pop();
                    if (regex[top] == '|') {
                        addEdge(top, i);
                        addEdge(parenthesis.top(), top+1);
                    }
                }
                ant = symbols.top();
                symbols.pop();
                parenthesis.pop();
            }

            if (i < regex.length()-1 && regex[i+1] == '*') {
                addEdge(ant, i+1);
                addEdge(i+1, ant);
            }

            if (regex[i] == '(' || regex[i] == ')' || regex[i] == '*')
                addEdge(i, i+1);
        }

    }

    void printGraph() {
        for (int i = 0; i < V; ++i) {
            std::cout << "Vertex " << i << " '" << vertices[i] << "': ";
            for (int j : adj[i]) {
                std::cout << j << ":" << vertices[j] << " ";
            }
            std::cout << std::endl;
        }
    }

    int size() {
        return V;
    }
};
