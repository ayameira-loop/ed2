#include <iostream>
#include <string>
#include <algorithm>
#include "VetorDinamicoOrdenado.h"
#include "Palavra.h"

// cat .\moreWords | ./main

using namespace std;

std::string removeCharacters(std::string str) {
    std::string result = str;
    result.erase(std::remove_if(result.begin(), result.end(), [](char c) {
        return (c == ',' || c == '.' || c == '(' || c == ')' || c == ';' || c == '"');
    }), result.end());
    return result;
}

void removeDuplicates(std::string* arr, int size)
{
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] == "") continue;  // Skip already removed elements

        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                arr[j] = "";  // Mark duplicate as empty string
            }
        }
    }
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
    }
    VetorDinamicoOrdenado<std::string, Palavra> vdo;

    for (size_t i = 0; i < N; i++) {
        std::string cleanWord = removeCharacters(words[i]);
        cleanWords[i] = cleanWord;
        Palavra p = Palavra(cleanWord);
        vdo.add(cleanWord, p);
    }

    vdo.show();

    // F: palavras mais frequentes
    int highestF = 1;
    int tamHighest = 0; // numero de palavras q ocorreram highestF vezes
    std::string highest[N];

    for (int i = 0; i < N; i++) {
        std::string word = cleanWords[i];
        Palavra p = vdo.value(word);
        if (p.getOcorrencias() > highestF) {
            highestF = p.getOcorrencias();
            highest[0] = word;
            tamHighest = 1;
        } else if (p.getOcorrencias() == highestF) {
            highest[tamHighest] = word;
            tamHighest++;
        }
    }
    removeDuplicates(highest, tamHighest);
    std::cout << "Palavra(s) mais frequente(s) (frequencia = " << highestF << "): " << std::endl;
    for (int i = 0; i < tamHighest; i++) {
        if (highest[i] != "") {
            std::cout << highest[i] << std::endl;
        }
    }

    // O: dada uma palavra, quantas vezes ocorre no texto

    // L: quais as palavras mais longas
    int length = 1;
    int tamLongest = 0; // numero de palavras q tem length tamanho
    std::string longest_words[N];

    for (int i = 0; i < N; i++) {
        std::string word = cleanWords[i];
        Palavra p = vdo.value(word);
        if (p.getNumLetras() > length) {
            length = p.getNumLetras();
            longest_words[0] = word;
            tamLongest = 1;
        } else if (p.getNumLetras() == length) {
            longest_words[tamLongest] = word;
            tamLongest++;
        }
    }
    removeDuplicates(highest, tamLongest);
    std::cout << "Palavra(s) mais longa(s) (# letras = " << length << "): " << std::endl;
    for (int i = 0; i < tamLongest; i++) {
        if (longest_words[i] != "") {
            std::cout << longest_words[i] << std::endl;
        }
    }

    // SR: quais as maiores palavras que nao repetem letras
    int lengthSR = 1;
    int tamLongestSR = 0; // numero de palavras q tem lengthSR tamanho
    std::string longest_words_SR[N];

    for (int i = 0; i < N; i++) {
        std::string word = cleanWords[i];
        Palavra p = vdo.value(word);
        if (p.getTemRepetida()) continue;
        if (p.getNumLetras() > lengthSR) {
            lengthSR = p.getNumLetras();
            longest_words_SR[0] = word;
            tamLongestSR = 1;
        } else if (p.getNumLetras() == lengthSR) {
            longest_words_SR[tamLongestSR] = word;
            tamLongestSR++;
        }
    }
    removeDuplicates(highest, tamLongestSR);
    std::cout << "Palavra(s) mais longa(s) sem letras repetidas (# letras = " << lengthSR << "): " << std::endl;
    for (int i = 0; i < tamLongestSR; i++) {
        if (longest_words_SR[i] != "") {
            std::cout << longest_words_SR[i] << std::endl;
        }
    }

    // VD: quais as menores palavras com mais vogais sem repeticao
    int mostVowels = 1;
    int tamMost = 0; // numero de palavras q tem lengthSR tamanho
    std::string wordsWithMostVowels[N];

    for (int i = 0; i < N; i++) {
        std::string word = cleanWords[i];
        Palavra p = vdo.value(word);
        if (p.getNumVogaisSemRepeticao() > mostVowels) {
            mostVowels = p.getNumVogaisSemRepeticao();
            wordsWithMostVowels[0] = word;
            tamMost = 1;
        } else if (p.getNumVogaisSemRepeticao() == mostVowels) {
            wordsWithMostVowels[tamMost] = word;
            tamMost++;
        }
    }
    removeDuplicates(highest, tamMost);
    std::cout << "Palavra(s) com mais vogais sem repetição (# vogais = " << mostVowels << "): " << std::endl;

    int shortestLengthVD = 5000;
    // encontra menor palavra em wordsWithMostVowels
    for (int i = 0; i < tamMost; i++) {
        if (wordsWithMostVowels[i] != "") {
            int len = wordsWithMostVowels[i].length();
            if (len < shortestLengthVD) {
                shortestLengthVD = length;
            }
        }
    }
    // printa todas as palavras com esse tamanho
    for (int i = 0; i < tamMost; i++) {
        if (wordsWithMostVowels[i].length() == shortestLengthVD) {
            std::cout << wordsWithMostVowels[i] << std::endl;
        }
    }
    
    return 0;
}


