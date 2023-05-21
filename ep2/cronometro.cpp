#include <iostream>
#include <chrono>
#include <algorithm>
#include "VetorDinamicoOrdenado.h"
#include "Palavra.h"
#include "Treap.h"
#include "ArvoreBuscaBinaria.h"
#include "RBTree.h"
// cat .\moreWords | ./crono
// cat .\fullSherlock | ./crono
// cat .\bigSherlock | ./crono
// cat .\A_travers_les_cactus | ./crono

std::string removeCharacters(std::string str) {
    std::string result = str;
    result.erase(std::remove_if(result.begin(), result.end(), [](char c) {
        return (c == ',' || c == '.' || c == '(' || c == ')' || c == ';' || c == '"');
    }), result.end());
    return result;
}

template<typename E>
void testTime(E estrutura, std::string words[], int N) {
    std::clock_t start_montagem, start_consultas;
    double duration;

    start_montagem = std::clock();
    for (int i = 0; i < N; i++) {
        Palavra p = Palavra(words[i]);
        estrutura.add(words[i], p);
    }
    duration = ( std::clock() - start_montagem ) / (double) CLOCKS_PER_SEC;
    std::cout << "Tempo para montar a tabela: " << duration << " ms" << std::endl;

    start_consultas = std::clock();
    for (int i = 0; i < N; i++) {
        estrutura.value(words[i]);
    }
    duration = ( std::clock() - start_consultas ) / (double) CLOCKS_PER_SEC;
    std::cout << "Tempo para fazer " << N << " consultas a tabela: " << duration << " ms" << std::endl;
}

int main() {
    // build array with N words
    std::string E;
    std::cin >> E;
    std::cout << E << std::endl; 
    int N; 
    std::cin >> N;
    std::string words[N];
    std::string cleanWords[N];

    for (int i = 0; i < N; i++) {
        std::cin >> words[i];
    }
    
    for (int i = 0; i < N; i++) {
        std::string cleanWord = removeCharacters(words[i]);
        cleanWords[i] = cleanWord;
    }

    if (E == "VO") {
        VetorDinamicoOrdenado<std::string, Palavra> estrutura;
        testTime(estrutura, cleanWords, N);

    } else if (E == "ABB") {
        ArvoreBuscaBinaria<std::string, Palavra> estrutura;
        testTime(estrutura, cleanWords, N);

    } else if (E == "TR") {
        Treap<std::string, Palavra> estrutura;
        testTime(estrutura, cleanWords, N);

    } else if (E == "ARN") {
        RBTree<std::string, Palavra> estrutura;
        testTime(estrutura, cleanWords, N);

    } else {
        std::cout << "Invalid data structure" << std::endl;
        return -1;
    }


    return 0;
}
