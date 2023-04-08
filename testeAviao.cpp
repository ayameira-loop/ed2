#include <iostream>
#include <string>
#include <cstdlib>
#include "Aviao.h"
#include "LinkedList.h"

int calculaMediaCombustivelEspera(LinkedList<Aviao> fila) {
    int totalComb = 0; // total de combustivel dos avioes esperando para pousar
    int npousos = 0; // n de avioes esperando para pousar
    for (int i = fila.size()-1; i >= 0; i--) { // atualiza as estimativas 
        std::cout << i << std::endl;

        if (fila.at(i)->getEvento() == 0) {
            totalComb = totalComb + fila.at(i)->getCombustivel();
            npousos++;
        }
    }
    if (npousos > 0) {
        std::cout << "resp : " << totalComb / npousos << std::endl;
        return totalComb / npousos;
    }
    else {
        std::cout << 0 << std::endl;
        return 0;
    }
}


int main() {
    int T = 50; // unidades de tempo de simula ̧c ̃ao;
    int K = 4; // n ́umero m ́aximo de avi ̃oes que chegam no aeroporto em cada unidade de tempo;
    float pp = 0.5;// probabilidade de ser um pouso;
    float pd = 1 - pp;// probabilidade de ser decolagem (1.0 − pp);
    int pe = 0.03; // probabilidade de ser emergˆencia;
    int C = 20; // tempo m ́aximo de combust ́ıvel de um avi ̃ao que deseja pousar;
    int V = 100; // tempo m ́aximo de voo de uma decolagem.

    srand(123);

    LinkedList<Aviao> fila;

    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int k = 5;
    for (int i = 0; i < k; i++) {
        Aviao* newAviao = new Aviao(C, V, pe);
        fila.enqueue(newAviao);
    }
    std::cout << "antes" << std::endl;
    for (int i = fila.size()-1; i >= 0; i--) {
        std::cout << i << " - ";
        fila.at(i)->printInfo();
    }

    calculaMediaCombustivelEspera(fila);
    //std::cout << res << std::endl;

    
}