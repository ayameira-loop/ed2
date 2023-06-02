#include <iostream>
#include <string>
#include <algorithm>
#include "A23.h"
#include "TSArvore23.h"

#include "Palavra.h"

std::string removeCharacters(std::string str) {
    std::string result = str;
    result.erase(std::remove_if(result.begin(), result.end(), [](char c) {
        return (c == ',' || c == '.' || c == '(' || c == ')' || c == ';' || c == '"');
    }), result.end());
    return result;
}


int main() {
    TSArvore23<std::string, Palavra> estrutura;
    int i, count = 0;
    std::string E;
    std::cin >> E;


    // build array with N words
    int N; 
    std::cin >> N;
    std::string words[N];
    for (int i = 0; i < N; i++) {
        std::cin >> words[i];
    }

    // populate structure
    std::string cleanWords[N];
    for (int i = 0; i < N; i++) {
        std::string cleanWord = removeCharacters(words[i]);
        cleanWords[i] = cleanWord;
        Palavra p = Palavra(cleanWord);
        estrutura.add(cleanWord, p);
    }

    estrutura.print();
    return 0;
}