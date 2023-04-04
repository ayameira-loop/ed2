#include <iostream>
#include <string>
#include <cstdlib>
#include "Aviao.h"
#include "LinkedList.h"

int main() {
    int T = 50; // unidades de tempo de simula ̧c ̃ao;
    int K = 4; // n ́umero m ́aximo de avi ̃oes que chegam no aeroporto em cada unidade de tempo;
    float pp = 0.5;// probabilidade de ser um pouso;
    float pd = 1 - pp;// probabilidade de ser decolagem (1.0 − pp);
    int pe = 0.03; // probabilidade de ser emergˆencia;
    int C = 20; // tempo m ́aximo de combust ́ıvel de um avi ̃ao que deseja pousar;
    int V = 100; // tempo m ́aximo de voo de uma decolagem.

    srand(123);

    LinkedList<Aviao> listaDeAvioes;

    Aviao aviaoA(C, V, pe);
    Aviao aviaoB(C, V, pe);
    Aviao aviaoC(C, V, pe);
    Aviao aviaoD(C, V, pe);
    listaDeAvioes.add(&aviaoA);
    listaDeAvioes.add(&aviaoB);
    listaDeAvioes.add(&aviaoC);
    listaDeAvioes.add(&aviaoD);
    std::cout << "Size of listaDeAvioes: " << listaDeAvioes.size() << std::endl;
    std::cout << "Values in listaDeAvioes: ";
    for (int i = 0; i < listaDeAvioes.size(); i++) {
        // Aviao* aviaoPtr = listaDeAvioes.at(i);
        // Aviao aviao = *aviaoPtr;
        // aviao.printInfo();
        listaDeAvioes.at(i)->printInfo();
    }
    std::cout << std::endl;
    return 0;
}