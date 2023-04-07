#include <iostream>
#include <string>
#include <cmath>
#include "LinkedList.h"
#include "Aviao.h"
#include "Aeroporto.h"

float calculaMediaCombustivelEspera(LinkedList<Aviao> fila) {
    int totalComb = 0; // total de combustivel dos avioes esperando para pousar
    int npousos = 0; // n de avioes esperando para pousar
    for (int i = fila.size()-1; i >= 0; i--) { // atualiza as estimativas 
        if (fila.at(i)->getEvento() == 0) {
            totalComb = totalComb + fila.at(i)->getCombustivel();
            npousos++;
        }
    }
    if (npousos > 0)
        return static_cast<float>(totalComb) / npousos;
    else
        return 0.0;
}

int main() {

    int T = 100; // unidades de tempo de simula ̧c ̃ao;
    int K = 4; // n ́umero m ́aximo de avioes que chegam no aeroporto em cada unidade de tempo;
    float pp = 0.5;// probabilidade de ser um pouso;
    float pd = 1 - pp;// probabilidade de ser decolagem (1.0 − pp);
    float pe = 0; // probabilidade de ser emergˆencia;
    int C = 50; // tempo m ́aximo de combustivel de um avi ̃ao que deseja pousar;
    int V = 100; // tempo m ́aximo de voo de uma decolagem.
    srand(123);
    int t = 0;
    // pista 1: pouso e decolagem
    // pista 2: pouso e decolagem
    // pista 3: decolagem, pouso só em emergência
    // tanto o pouso quanto a decolagem demoram 3 unidades de tempo
    //pista tem 3 estados { uso, intermissão, livre }
    
    int houveEmergencia = 0; // se houve emergencia, minhas estimativas de espera precisam ser recalculadas
    int estimD = 0;
    int estimP = 0;
    int tempoGlobalEsperaP = 0;
    int tempoGlobalEsperaD = 0;
    int qtdGlobalCombustivel = 0;
    int nGlobalD = 0;
    int nGlobalP = 0;
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
        aeroporto.printStatus();

        for (int i = 0; i < k; i++) {
            Aviao* novoAviao = new Aviao(C, V, pe);
            novoAviao->setEst(aeroporto.estimador(novoAviao->getEvento(), aeroporto.getPousos(), aeroporto.getDecolagens()));
            novoAviao->setEstIni(aeroporto.estimador(novoAviao->getEvento(), aeroporto.getPousos(), aeroporto.getDecolagens()) + 4);
            if (novoAviao->getEmergencia()) { // avião tem que receber autorização imediata para utilizar a pista
                fila.insertEmergency(novoAviao);
            } else {
                fila.enqueue(novoAviao);
            }
            aeroporto.incrementQueue(novoAviao->getEvento());
        }

        int npousos = 0;
        int ndecolagens = 0;
        for (int i = fila.size()-1; i >= 0; i--) { // atualiza as estimativas 
            fila.at(i)->setEst(aeroporto.estimador(fila.at(i)->getEvento(), npousos, ndecolagens));
            if (fila.at(i)->getEvento() == 1)
                ndecolagens++;
            else
                npousos++;
        }

        for (int i = fila.size()-1; i >= 0; i--) {
            std::cout << i << " - ";
            fila.at(i)->printInfo();
        }

        // uso das pistas até que não haja nenhum avião na fila ou não haja pista disponível
        while (fila.size() > 0) { 
            Aviao* aviao = fila.frontOfTheLine();
            int pistaDisponivel = aeroporto.useAvailable(*aviao);
            if (pistaDisponivel != -1) {
                Aviao* aviao = fila.dequeue();
                int evento = aviao->getEvento();
                aeroporto.decrementQueue(evento);
                if (evento == 1) {
                    tempoGlobalEsperaD = tempoGlobalEsperaD + aviao->getTnf();
                    nGlobalD++;
                }
                else {
                    tempoGlobalEsperaP = tempoGlobalEsperaP + aviao->getTnf();
                    qtdGlobalCombustivel = qtdGlobalCombustivel + aviao->getCombustivel();
                    nGlobalP++;
                }
            }
            else 
                break;
        }

        // atualiza os valores da iteração
        for (int i = fila.size()-1; i >= 0; i--) {
            fila.at(i)->atualizaCombustivel();
        }
        aeroporto.updateStatusPistas();
        /* só prints
            int totalComb = 0; // total de combustivel dos avioes esperando para pousar
            int n_pousos = 0; // n de avioes esperando para pousar
            for (int i = fila.size()-1; i >= 0; i--) { // atualiza as estimativas 
                if (fila.at(i)->getEvento() == 0) {
                    totalComb = totalComb + fila.at(i)->getCombustivel();
                    n_pousos++;
                }
            }
            if (n_pousos > 0)
                std::cout << "quantidade media de combustivel dos avioes esperando para pousar: " << static_cast<float>(totalComb) / n_pousos << std::endl;

            if (nGlobalD > 0) {
                std::cout << "tempo medio de espera para decolagem: " << static_cast<float>(tempoGlobalEsperaD) / nGlobalD << std::endl;
            } 
            if (nGlobalP > 0) {
                std::cout << "tempo medio de espera para pouso: " << static_cast<float>(tempoGlobalEsperaP) / nGlobalP << std::endl;
            } 
            if (nGlobalP > 0) {
                std::cout << "quantidade media de combustivel disponivel dos avioes que pousaram: " << static_cast<float>(qtdGlobalCombustivel) / nGlobalP << std::endl;
            } 
        */
        t++;
    }
}