#include <iostream>
#include <string>
#include <algorithm>
#include "VetorDinamicoOrdenado.h"
#include "Palavra.h"

// cat .\mywords | ./ini

using namespace std;

std::string removeCharacters(std::string str) {
    std::string result = str;
    result.erase(std::remove_if(result.begin(), result.end(), [](char c) {
        return (c == ',' || c == '.' || c == '(' || c == ')' || c == ';' || c == '"');
    }), result.end());
    return result;
}


int main() {
    int N; 
    int i, count = 0;
    cout << "N: ";
    cin >> N;
    std::string words[N];
    std::string cleanWords[N];
    cout << N << endl;
    for (int i = 0; i < N; i++) {
        cin >> words[i];
        cout << words[i] << endl;
    }
    VetorDinamicoOrdenado<std::string, Palavra> vdo;

    for (size_t i = 0; i < N; i++) {
        std::string cleanWord = removeCharacters(words[i]);
        cleanWords[i] = cleanWord;
        Palavra p = Palavra(cleanWord);
        vdo.add(cleanWord, p);
    }

    std::cout << "now print" << std::endl;
    vdo.show();

    for (size_t i = 0; i < N; i++) {
        std::cout << cleanWords[i] << ": " << vdo.value(cleanWords[i]).toString() << std::endl;
    }
    //vdo.mostFrequent();

    //int n = vdo.getFrequency("as");
    //std::cout << n << endl;

    //vdo.longest();

    return 0;
}


