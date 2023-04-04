#include <iostream>
#include <string>
#include "LinkedList.h"

int main() {

    int T = 50; // unidades de tempo de simula ̧c ̃ao;
    int K = 4; // n ́umero m ́aximo de avi ̃oes que chegam no aeroporto em cada unidade de tempo;
    float pp = 0.5;// probabilidade de ser um pouso;
    float pd = 1 - pp;// probabilidade de ser decolagem (1.0 − pp);
    int pe = 0.03; // probabilidade de ser emergˆencia;
    int C = 20; // tempo m ́aximo de combust ́ıvel de um avi ̃ao que deseja pousar;
    int V = 100; // tempo m ́aximo de voo de uma decolagem.

    // id do avião: AA-DDD
        // AA: companhia aérea
        // DDD: três dígitos
    // Origem: string
    // Destino: string
    // combustível: 1 a C unidades de tempo
    // tempo estimado de voo: 1 a V unidades de tempo
    // ehEmergencia: bool com p(E). deve ter passagem livre para aterrissar/decolar

    // pista 1: pouso e decolagem
    // pista 2: pouso e decolagem
    // pista 3: decolagem, pouso só em emergência
    // tanto o pouso quanto a decolagem demoram 3 unidades de tempo

    // situação crítica: 4 ou mais aviões ficarão sem combustível ao mesmo tempo
        // pode enviar para aeroportos vizinhos
    
    // preferências:
        // emergências, aviões que estão esperando para decolar por mais de 10% do tempo de voo

    while (t < T) {
        int K = random()
        t++;
    }
}