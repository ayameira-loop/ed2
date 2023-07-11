#include "Graph.cpp"
#include <stack>
#include <vector>
#include <iostream>
#include <string.h>
using namespace std;

bool reconhece(string word, Graph G) {
    string regex = G.getRegex();
    vector<bool> atingidos(G.size(), false);
    G.dfs(0, atingidos);
    
    for (int i=0; i < word.length(); i++) {
        vector<bool> prox(G.size(), false);
        for (int j=0; j < atingidos.size()-1; j++) {
            if (atingidos[j] && (regex[j] == word[i] || regex[j] == '.')) {
                prox[j+1] = true;
                cout << "leio " << regex[j] << endl;
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

string treatRegex(string regex) {
    stack<char> newString;
    stack<int> brackets;

    
    for (int i=0; i<regex.length(); i++) {
        if (regex[i] == '[') {
            brackets.push(i);
        }
        if (regex[i] == ']') {
            brackets.push(i);
        }
    }
    string substring = "";
    while (brackets.size() > 1) {
        int end = brackets.top();
        brackets.pop();
        int start = brackets.top();
        brackets.pop();
        substring = regex.substr(start + 1, end - start - 1);
        // Checa se é um conjunto ou intervalo ou complemento
        string expandedSubset = "";
        if (substring.length() > 2 && substring[1] == '-') {
            // intervalo
            char rangeStart = substring[0];
            char rangeEnd = substring[2];
            
            // Expand the range subset
            for (char c = rangeStart; c <= rangeEnd; ++c) {
                expandedSubset += c;
                if (c != rangeEnd) {
                    expandedSubset += '|';
                }
            }
        } else  if (substring.length() > 1 && substring[0] == '^') { // complemento
            char c = substring[1];
            char startChar = static_cast<char>(0);
            char endChar = static_cast<char>(127);
            if (isalpha(c)) {
                if (islower(c)) {
                    startChar = 'a';
                    endChar = 'z';
                } else if (isupper(c)) {
                    startChar = 'A';
                    endChar = 'Z';
                }
            } else if (isdigit(c)) {
                startChar = '0';
                endChar = '9';

            }
            for (char c = startChar; c <= endChar; c++) {
                if (substring.find(c) == std::string::npos) {
                    expandedSubset += c;
                    if (c != endChar) {
                        expandedSubset += '|';
                    }
                }
            }            

        } else {
            // conjunto
            for (int i=0; i < substring.length(); i++) {
                expandedSubset += substring[i];
                if (i != substring.length()-1) {
                    expandedSubset += '|';
                }
            }
        }
        regex.replace(start, end - start + 1, "(" + expandedSubset + ")");
        cout << regex << endl;    
    }
    return regex;
    // conjuntos []
    // intervalos [-]
    // complementos [^]
    // um ou mais +

}
int main(void) {
    string re = "[^AEIOU][AEIOU][^AEIOU][AEIOU]";

    string regex = treatRegex(re);

    Graph G(regex.length()+1, regex);
    G.createNFA();
    G.printGraph();

    string word = "BELO";
    cout << "reconhece '" << word << "'?" << endl;
    cout << reconhece(word, G) << endl;
    return 0;
} 