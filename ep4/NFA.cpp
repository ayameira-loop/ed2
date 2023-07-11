#include "NFA.h"

NFA::NFA(string regex) : regex(regex), G(regex.length() + 1) {
        for (int i = 0; i < regex.length(); i++)
            G.setVertexValue(i, regex[i]);

        stack<int>symbols;
        stack<int>parenthesis;

        for (int i=0; i < regex.length(); i++) {
            int ant = i;

            if (regex[i] == '\\') {
                G.addEdge(i, i+1);
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
                        G.addEdge(top, i);
                        G.addEdge(parenthesis.top(), top+1);
                    }
                }
                ant = symbols.top();
                symbols.pop();
                parenthesis.pop();
            }

            if (i < regex.length()-1 && regex[i+1] == '*') {
                G.addEdge(ant, i+1);
                G.addEdge(i+1, ant);
            }

            if (regex[i] == '(' || regex[i] == ')' || regex[i] == '*')
                G.addEdge(i, i+1);
        }
    }

string NFA::getRegex() {
    return regex;
}

void NFA::show() {
    G.printGraph();
}

bool NFA::reconhece(string word) {
    vector<bool> atingidos(G.size(), false);
    G.dfs(0, atingidos);
    
    for (int i=0; i < word.length(); i++) {
        vector<bool> prox(G.size(), false);
        for (int j=0; j < atingidos.size()-1; j++) {
            if (atingidos[j] && (regex[j] == word[i] || regex[j] == '.')) {
                prox[j+1] = true;
            }
        }
        vector<bool> marc(G.size());
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
