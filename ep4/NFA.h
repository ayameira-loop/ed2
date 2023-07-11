#ifndef NFA_H
#define NFA_H

#include "Graph.h"
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

class NFA {
private:
    string regex;
    Graph G;

public:
    NFA(string regex);

    string getRegex();
    void show();
    bool reconhece(string word);
};

#endif
