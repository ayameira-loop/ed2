#include "Graph.cpp"
#include <stack>
#include <vector>
#include <iostream>
#include <string.h>
using namespace std;
/*
bool reconhece(std::string word, Graph G) {
    std::vector<bool> marked(G.size(), false);
    std::stack<int> reached;
    std::string regex = G.getRegex();
    G.dfs(0, marked);
    for (int i=0; i < word.length(); i++) {
        for (int j=0; j < marked.size()-1; j++) {
            if (marked[j] && (regex[j] == word[i] || ((j-1 < 0 || regex[j-1] != '\\')&& regex[j] == '.')) ) {
                std::cout << "Leio " << marked[j] << std::endl;
                reached.push(j+1);
            }
        }
        for (int k=0; k < marked.size(); k++) {
            marked[k] = false;
        }
        while (!reached.empty()) {
            G.dfs(reached.top(), marked);
            reached.pop();
        }
    }
    //marked[regex.length()] == Estado de aceitação
    return marked[regex.length()];
}
*/
bool reconhece(std::string word, Graph G) {
    std::string regex = G.getRegex();
    std::vector<bool> atingidos(G.size(), false);
    G.dfs(0, atingidos);
    
    for (int i=0; i < word.length(); i++) {
        std::vector<bool> prox(G.size(), false);
        for (int j=0; j < atingidos.size()-1; j++) {
            if (atingidos[j] && (regex[j] == word[i] || regex[j] == '.')) {
                prox[j+1] = true;//
            }
        }
        std::vector<bool> marc(G.size());
        for (int k=0; k < atingidos.size(); k++)    atingidos[k] = false;
        for (int j=0; j < G.size(); j++) {
            if (prox[j]) {
                for (int k=0; k<G.size(); k++)  marc[k] = false;
                G.dfs(j, marc);
                for (int k=0; k<G.size(); k++)
                    if (marc[k])
                        atingidos[k] = true;
            }
        }
    }
    return atingidos[G.size()-1];
}
int main(void) {
    std::string re = "(A*CG|A*TA|AAG*T)*";

    Graph G(re.length()+1, re);
    G.createNFA();
    G.printGraph();

    std::string word = "ACGTA";
    std::cout << "reconhece '" << word << "'?" << std::endl;
    std::cout << reconhece(word, G) << std::endl;
    

    return 0;
} 