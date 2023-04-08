#include <iostream>
#include <string>
#include <string.h>
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
    int K = 3; // n ́umero m ́aximo de avioes que chegam no aeroporto em cada unidade de tempo;
    float pp = 0.75;// probabilidade de ser um pouso;
    float pd = 1 - pp;// probabilidade de ser decolagem (1.0 − pp);
    float pe = 0; // probabilidade de ser emergˆencia;
    int C = 50; // tempo m ́aximo de combustivel de um avi ̃ao que deseja pousar;
    int V = 100; // tempo m ́aximo de voo de uma decolagem.
    srand(123);
    int t = 0;
    int v = false; // verbose
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

    LinkedList<Aviao> fila;
    Aeroporto aeroporto;

    while (t < T) {
        int k = rand() % K + 1; // numero de aviões que informam que querem decolar/pousar em t
        std::cout << "TEMPO: " << t << " | adiciona " << k << std::endl;
        aeroporto.printStatus();

        for (int i = 0; i < k; i++) {
            Aviao* novoAviao = new Aviao(C, V, pe);
            novoAviao->setEst(aeroporto.estimador(novoAviao->getEvento(), aeroporto.getPousos(), aeroporto.getDecolagens()));

            if (novoAviao->getEmergencia()) { 
                // se for emergencia, avião tem que receber autorização imediata para utilizar a pista
                fila.insertEmergency(novoAviao);
            } else {
                fila.enqueue(novoAviao);
            }
            aeroporto.incrementQueue(novoAviao->getEvento());
        }
        for (int i = fila.size()-1; i >= 0; i--) {
            if (fila.at(i)->getEvento() == 0) { // se um avião que quer pousar vai ficar sem combustível, trocar por algum outro voo (decolagem qualquer ou pouso que tenha mais combustível)
                int trocou = false;
                if (fila.at(i)->getEst() > fila.at(i)->getCombustivel()) {
                    if (v)
                        std::cout << "aviao " << fila.at(i)->getID() << " vai ficar sem comb " << std::endl;
                    for (int j = i+1; j < fila.size(); j++) {
                        if (fila.at(j)->getEst() < fila.at(i)->getCombustivel()) {
                            if (fila.at(j)->getEvento() == 0 && fila.at(j)->getCombustivel() > fila.at(i)->getCombustivel() ) {
                                if (v) {
                                    std::cout << "move " << i << " to " << j << std::endl;
                                    std::cout << "00 - coloca o " << fila.at(i)->getID() << " no " << fila.at(j)->getID() << std::endl;
                                }
                                fila.moveTo(i, j);
                                trocou = true;
                                break;
                            }
                            // se o voo que vai ser preterido for decolagem, nao posso preterir se já tiver passado 10% do TEV na fila
                            if (fila.at(j)->getEvento() == 1 && fila.at(j)->getTnf() < (fila.at(j)->getTev() * 0.1)) {
                                if (v) {
                                    std::cout << "move " << i << " to " << j << std::endl;
                                    std::cout << "01 - coloca o " << fila.at(i)->getID() << " no " << fila.at(j)->getID() << std::endl;
                                }
                                fila.moveTo(i, j);
                                trocou = true;
                                break;
                            }
                        }
                    }
                    if (trocou == false) {
                        std::cout << "nao conseguiu fazer a troca do " << fila.at(i)->getID() << " foi encaminhado para outro aeroporto" << std::endl;
                        Aviao* aviao = fila.remove(i);
                        int evento = aviao->getEvento();
                        aeroporto.decrementQueue(evento);
                    }
                }
            }
            if (fila.at(i)->getEvento() == 1) {
                if (fila.at(i)->getTnf() > 0.1 * fila.at(i)->getTev()) {
                    if (v)
                        std::cout << "o aviao " << fila.at(i)->getID() << " ja esperou demais" << std::endl;
                    for (int j = i+1; j < fila.size(); j++) {
                        if (fila.at(j)->getEvento() == 1) {
                            if (fila.at(j)->getTnf() < 0.1 * fila.at(j)->getTev()) {
                                if (v) {
                                    std::cout << "move " << i << " to " << j << std::endl;
                                    std::cout << "11 - coloca o " << fila.at(i)->getID() << " no " << fila.at(j)->getID() << std::endl;
                                }
                                fila.moveTo(i, j);
                                break;
                            }
                        } else {
                            if (fila.at(j)->getCombustivel() > fila.at(j)->getEst()) {
                                if (v) {
                                    std::cout << "move " << i << " to " << j << std::endl;
                                    std::cout << "10 - coloca o " << fila.at(i)->getID() << " no " << fila.at(j)->getID() << std::endl;
                                }
                                fila.moveTo(i, j);
                                break;
                            }
                        }
                    }
                }
            }
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

        if (v) {
            for (int i = fila.size()-1; i >= 0; i--) {
                std::cout << i << " - ";
                fila.at(i)->printInfo();
            }
        }

        // uso das pistas até que não haja nenhum avião na fila ou não haja pista disponível
            // pega o primeiro
            // tenta useAvailable()
            // se não der, pega o seguinte
        int idx = fila.size()-1;
        while (fila.size() > 0 && aeroporto.existsAvailable() && idx >= 0) { 
            Aviao* aviao = fila.at(idx);
            int pistaDisponivel = aeroporto.useAvailable(*aviao);
            if (pistaDisponivel != -1) {
                Aviao* aviao = fila.remove(idx);
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
            idx--;
        }

        // atualiza os valores da iteração
        for (int i = fila.size()-1; i >= 0; i--) {
            fila.at(i)->atualizaCombustivel();
        }
        aeroporto.updateStatusPistas();
        ///* só prints
            int totalComb = 0; // total de combustivel dos avioes esperando para pousar
            int n_pousos = 0; // n de avioes esperando para pousar
            for (int i = fila.size()-1; i >= 0; i--) { // atualiza as estimativas 
                if (fila.at(i)->getEvento() == 0) {
                    totalComb = totalComb + fila.at(i)->getCombustivel();
                    n_pousos++;
                }
            }

            if (nGlobalD > 0) {
                std::cout << "tempo medio de espera para decolagem: " << static_cast<float>(tempoGlobalEsperaD) / nGlobalD << std::endl;
            } 
            if (nGlobalP > 0) {
                std::cout << "tempo medio de espera para pouso: " << static_cast<float>(tempoGlobalEsperaP) / nGlobalP << std::endl;
            } 
            if (n_pousos > 0)
                std::cout << "quantidade media de combustivel dos avioes esperando para pousar: " << static_cast<float>(totalComb) / n_pousos << std::endl;
            if (nGlobalP > 0) {
                std::cout << "quantidade media de combustivel disponivel dos avioes que pousaram: " << static_cast<float>(qtdGlobalCombustivel) / nGlobalP << "\n\n";
            } 
        //*/
        t++;
    }
}