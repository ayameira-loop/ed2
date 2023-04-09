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
    
    vdo.show();

    return 0;
}


