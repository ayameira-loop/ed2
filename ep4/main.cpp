#include "Graph.h"
#include "NFA.cpp"
#include <stack>
#include <vector>
#include <iostream>
#include <string.h>
using namespace std;

string treatRegex(string regex) {
    stack<int> brackets;
    vector<int> paranthesis;
    
    for (int i=0; i<regex.length(); i++) {
        if (i == 0) {
            if (regex[i] == '[') brackets.push(i);
            if (regex[i] == ']') brackets.push(i);    
        } else {
            if (regex[i] == '[' && regex[i-1] != '\\') brackets.push(i);
            if (regex[i] == ']'&& regex[i-1] != '\\') brackets.push(i);
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
                if (substring.find(c) == string::npos) {
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
    }
    
    // um ou mais +
    for (int i=1; i<regex.length(); i++) {
        if (regex[i] == '+' && regex[i-1] != '\\') {
            string expression = "";
            if (regex[i-1] == ')') {
                int closeP = i-1; 
                int openP = 0; 
                int close = 0;
                int open = 0;
                for (int j=(i-1); j >= 0; j--) {
                    if (regex[j] == ')')
                        close++;
                    if (regex[j] == '(')
                        open++;
                    if (open == close) {
                        openP = j;
                        break;
                    }
                }
                for (int j=openP; j<=closeP; j++) {
                    expression += (regex[j]);
                }
            } else {
                expression += (regex[i-1]); 
            }
            expression+='*';
            regex.replace(i, 1, expression);
        }
    }
    return regex;
}

int main(void) {
    string re = "(([a-z])*|([0-9])*)*@(([a-z])+\\.)+br";
    re = treatRegex(re);
    NFA nfa(re);

    string word = "thilio@bbb.com.br";
    cout << "reconhece '" << word << "'?" << endl;
    cout << nfa.reconhece(word) << endl;
    return 0;
} 