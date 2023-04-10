#include <iostream>
#include <string>
#include "VetorDinamicoOrdenado.h"
#include "Palavra.h"

// cat .\mywords | ./ini

using namespace std;

int main() {
    int N;
    cout << "N: ";
    cin >> N;
    std::cout << std::endl;
    std::string words[N];

    for (int i = 0; i < N; i++) {
        cin >> words[i];
    }

    VetorDinamicoOrdenado<std::string, Palavra> vdo;

    for (size_t i = 0; i < N; i++)
    {
        //Palavra *p = new Palavra(words[i]);
        Palavra p = Palavra(words[i]);
        vdo.add(words[i], p);
    }
    
    vdo.mostFrequent();

    int n = vdo.getFrequency("as");
    std::cout << n << endl;

    vdo.longest();

    return 0;
}


