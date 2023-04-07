#include <iostream>
#include <string>
#include "Aeroporto.h"
#include "Aviao.h"

int main() {
    int T = 100; // unidades de tempo de simula ̧c ̃ao;
    int K = 4; // n ́umero m ́aximo de avi ̃oes que chegam no aeroporto em cada unidade de tempo;
    float pp = 0.5;// probabilidade de ser um pouso;
    float pd = 1 - pp;// probabilidade de ser decolagem (1.0 − pp);
    float pe = 0; // probabilidade de ser emergˆencia;
    int C = 50; // tempo m ́aximo de combust ́ıvel de um avi ̃ao que deseja pousar;
    int V = 100; // tempo m ́aximo de voo de uma decolagem.
    srand(123);
    int t = 0;

    Aeroporto aeroporto;
    Aviao* novoAviao = new Aviao(C, V, pe);
    aeroporto.useAvailable(*novoAviao);
    aeroporto.incrementQueue(1);
    int evento = 0;
    //std::cout << aeroporto.estimador(evento, aeroporto.getPousos(), aeroporto.getDecolagens()) << std::endl;
    aeroporto.updateStatusPistas();
    aeroporto.printStatus();
    std::cout << aeroporto.estimador(evento, 0, 0) << std::endl;
    return 0;
}
