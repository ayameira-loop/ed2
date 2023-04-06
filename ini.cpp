#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Aviao.h"
#include "Aeroporto.h"


int main() {

    int T = 5; // unidades de tempo de simula ̧c ̃ao;
    int K = 4; // n ́umero m ́aximo de avi ̃oes que chegam no aeroporto em cada unidade de tempo;
    float pp = 0.5;// probabilidade de ser um pouso;
    float pd = 1 - pp;// probabilidade de ser decolagem (1.0 − pp);
    float pe = 0.1; // probabilidade de ser emergˆencia;
    int C = 20; // tempo m ́aximo de combust ́ıvel de um avi ̃ao que deseja pousar;
    int V = 100; // tempo m ́aximo de voo de uma decolagem.
    srand(123);
    int t = 0;
    // pista 1: pouso e decolagem
    // pista 2: pouso e decolagem
    // pista 3: decolagem, pouso só em emergência
    // tanto o pouso quanto a decolagem demoram 3 unidades de tempo
    //pista tem 3 estados { uso, intermissão, livre }
    
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    /*
    // triagem
    for (int i = 0; i < k; i++) {
        Aviao novoAviao(C, V, pe);
        
        se for causar situação crítica, já manda pra outro aeroporto
        
        se for emergencia, coloca no topo da fila (e se o topo for outra emergência?)

        se não, enqueue


    }

        se virar prioridade, coloca depois da última emergência
    */

    // situação crítica: 4 ou mais aviões ficarão sem combustível ao mesmo tempo
        // pode enviar para aeroportos vizinhos
    
    // preferências:
        // emergências, aviões que estão esperando para decolar por mais de 10% do tempo de voo

    LinkedList<Aviao> fila;
    Aeroporto aeroporto;

    while (t < T) {
        int k = rand() % K + 1; // numero de aviões que informam que querem decolar/pousar em t
        std::cout << "TEMPO: " << t << " | adiciona " << k << std::endl;

        for (int i = 0; i < k; i++) {
            Aviao* novoAviao = new Aviao(C, V, pe);
            //novoAviao->printInfo();
            fila.enqueue(novoAviao);
        }
        //std::cout << fila.frontOfTheLine()->getID() << std::endl;
        
        /*
        std::cout << "Fila no comeco: " << fila.size() << std::endl;

        for (int i = 0; i < fila.size(); i++) {
            std::cout << fila.at(i)->getID() << std::endl;
        }
        */

        while (fila.size() > 0) {
            Aviao* aviao = fila.frontOfTheLine();
            std::cout << "o oviao na frente da fila eh " << aviao->getID() << std::endl;
            int flight = aeroporto.useAvailable(*aviao);
            if (flight != -1) {
                Aviao* saiuDaFila = fila.dequeue();
                std::cout << "o oviao que saiu da fila eh " << saiuDaFila->getID() << std::endl;

            }
            else 
                break;
        }
        /*
        std::cout << "Fila no final: " << fila.size()<< std::endl;

        for (int i = 0; i < fila.size(); i++) {
            std::cout << fila.at(i)->getID() << std::endl;
        }*/

        aeroporto.updateStatus();
        t++;
    }
}