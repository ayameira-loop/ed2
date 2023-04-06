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

    int k = 3;
    for (int i = 0; i < k; i++) {
        Aviao* newAviao = new Aviao(C, V, pe);
        newAviao->printInfo();
        listaDeAvioes.enqueue(newAviao);
    }
    //std::cout << "Size of listaDeAvioes: " << listaDeAvioes.size() << std::endl;
    //std::cout << "Values in listaDeAvioes: ";
    //for (int i = 0; i < listaDeAvioes.size(); i++) {
    //    // Aviao* aviaoPtr = listaDeAvioes.at(i);
    //    // Aviao aviao = *aviaoPtr;
    //    // aviao.printInfo();
    //    listaDeAvioes.at(i)->printInfo();
    //}
    
    //std::cout << "front: " << listaDeAvioes.frontOfTheLine()->getID() << std::endl;
    //std::cout << "back: " << listaDeAvioes.backOfTheLine()->getID() << std::endl;
    int sz = listaDeAvioes.size();
    std::cout << "size: " << sz << std::endl;
    for (int i = 0; i < sz; i++) {
        Aviao* aviao = listaDeAvioes.dequeue();
        std::cout << "saiu: " << aviao->getID() << std::endl;
    }

    std::cout << std::endl;
    return 0;
}