#include "Graph.cpp"
#include <stack>
#include <vector>
#include <iostream>
#include <string.h>

bool reconhece(std::string word, Graph G) {
    std::vector<bool>marked(G.size(), false);
    std::stack<int>reached;
    std::string regex = G.getRegex();
    G.dfs(0, marked);
    for (int i=0; i < word.length(); i++){
        for (int j=0; j < marked.size()-1; j++){
            if (marked[j] && (regex[j] == word[i] || ((j-1 < 0 || regex[j-1] != '\\')&& regex[j] == '.')) ){
                //Leio e consigo chegar na próxima posição
                reached.push(j+1);
            }
        }
        for (int k=0; k < marked.size(); k++){
            marked[k] = false;
        }
        while (!reached.empty()){
            G.dfs(reached.top(), marked);
            reached.pop();
        }
    }
    //marked[regex.length()] == Estado de aceitação
    return marked[regex.length()];

}

int main(void) {
    std::string re = "A*(C|G)";
    Graph G(re.length()+1, re);
    G.createNFA();
    G.printGraph();

    std::string word = "ATACT";
    std::cout << "reconhece '" << word << "'?" << std::endl;
    //std::cout << reconhece(word, G) << std::endl;

    return 0;
} 