#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include "LinkedList.h"
#include "Aviao.h"
#include "Aeroporto.h"

void addNewPlanes(int k, LinkedList<Aviao>& fila, Aeroporto& aeroporto, int C, int V, float pe);
void printAllStatus(LinkedList<Aviao>& fila, Aeroporto& aeroporto, bool v, bool vv);
void treatExceptions(LinkedList<Aviao>& fila, Aeroporto& aeroporto, bool v, bool vv);
void updateEstimates(LinkedList<Aviao>& fila, Aeroporto& aeroporto);
void useLanes(LinkedList<Aviao>& fila, Aeroporto& aeroporto, int& nTotalEmerg, int& tempoTotalEsperaD, int& nTotalD, int& nTotalP, int& tempoTotalEsperaP, int& qtdTotalCombustivel, bool v);
void printSummary(LinkedList<Aviao>& fila, int nTotalEmerg, int tempoTotalEsperaD, int nTotalD, int nTotalP, int tempoTotalEsperaP, int qtdTotalCombustivel);

int main() {

    int T = 200; // unidades de tempo de simula ̧c ̃ao;
    int K = 2; // n ́umero m ́aximo de avioes que chegam no aeroporto em cada unidade de tempo;
    float pp = 0.75;// probabilidade de ser um pouso;
    float pd = 1 - pp;// probabilidade de ser decolagem (1.0 − pp);
    float pe = 0; // probabilidade de ser emergˆencia;
    int C = 75; // tempo m ́aximo de combustivel de um avi ̃ao que deseja pousar;
    int V = 1000; // tempo m ́aximo de voo de uma decolagem.
    srand(123);
    int t = 0;
    int verbose = false;
    int veryVerbose = false;

    int tempoTotalEsperaP = 0;
    int tempoTotalEsperaD = 0;
    int qtdTotalCombustivel = 0;
    int nTotalD = 0;
    int nTotalP = 0;
    int nTotalEmerg = 0;

    LinkedList<Aviao> fila;
    Aeroporto aeroporto;

    while (t < T) {
        int k = rand() % K + 1; // sorteia # de aviões que informam que querem decolar/pousar em t
        std::cout << "TEMPO: " << t << " | adiciona " << k << std::endl;

        addNewPlanes(k, fila, aeroporto, C, V, pe);
        printAllStatus(fila, aeroporto, verbose, veryVerbose);
        treatExceptions(fila, aeroporto, verbose, veryVerbose);
        updateEstimates(fila, aeroporto);
        useLanes(fila, aeroporto, nTotalEmerg, tempoTotalEsperaD, nTotalD, nTotalP, tempoTotalEsperaP, qtdTotalCombustivel, verbose);
        updateEstimates(fila, aeroporto);

        // atualiza os valores da iteração (diminui o combustível em uma unidade e incrementa o contador do status das pistas)
        for (int i = fila.size()-1; i >= 0; i--) {
            fila.at(i)->atualizaCombustivel();
        }
        aeroporto.updateStatusPistas();
        t++;
        printSummary(fila, nTotalEmerg, tempoTotalEsperaD, nTotalD, nTotalP, tempoTotalEsperaP, qtdTotalCombustivel);
    }

    return 0;
}

void addNewPlanes(int k, LinkedList<Aviao>& fila, Aeroporto& aeroporto, int C, int V, float pe) {
    // adiciona os novos avioes
    // se for emergencia, coloca na frente da fila
    // se nao, calcula a estimativa de tempo de espera e coloca no final da fila
    for (int i = 0; i < k; i++) {
        Aviao* novoAviao = new Aviao(C, V, pe);
        if (novoAviao->getEmergencia()) { 
            // se for emergencia, avião tem que receber autorização imediata para utilizar a pista
            fila.insertEmergency(novoAviao);
        } else {
            novoAviao->setEst(aeroporto.estimador(novoAviao->getEvento(), aeroporto.getPousos(), aeroporto.getDecolagens()));
            fila.enqueue(novoAviao);
        }
        aeroporto.incrementQueue(novoAviao->getEvento());
    }
}

void printAllStatus(LinkedList<Aviao>& fila, Aeroporto& aeroporto, bool v, bool vv) {
    if (v)
        aeroporto.printStatus();
    if (vv) {
        for (int i = fila.size()-1; i >= 0; i--) {
            std::cout << i << " - ";
            fila.at(i)->printInfo();
        }
    }
}
void treatExceptions(LinkedList<Aviao>& fila, Aeroporto& aeroporto, bool v, bool vv) {
    // trata as excecoes: 
    // antecipa quem vai ficar sem combustivel antes da estimativa de tempo de espera
    // dá status de emergencia para quem ja esperou mais 10% do tempo estimado de voo
    for (int i = fila.size()-1; i >= 0; i--) {
        Aviao* aviaoI = fila.at(i);
        if (aviaoI->getEvento() == 0) {  // POUSO
            // se um avião que quer pousar vai ficar sem combustível, trocar por algum outro voo (decolagem qualquer ou pouso que tenha mais combustível)
            int trocou = false;
            if (aviaoI->getEst() > aviaoI->getCombustivel()) {
                for (int j = i+1; j < fila.size(); j++) {
                    Aviao* aviaoJ = fila.at(j);
                    if (aviaoJ->getEst() < aviaoI->getCombustivel()) {
                        if (aviaoJ->getEvento() == 0 && aviaoJ->getCombustivel() > aviaoI->getCombustivel() ) {
                            if (v) {
                                std::cout << "O aviao " << aviaoI->getID() << "[" << i << "] foi remanejado para a posicao [" << j << "] (Combustivel baixo)" << std::endl;
                            }
                            fila.moveTo(i, j);
                            trocou = true;
                            break;
                        }
                        if (aviaoJ->getEvento() == 1 && aviaoJ->getTnf() < (aviaoJ->getTev() * 0.1)) {
                            // se o voo que vai ser preterido for decolagem, nao posso preterir se já tiver passado 10% do TEV na fila
                            if (v) {
                                std::cout << "O aviao " << aviaoI->getID() << "[" << i << "] foi remanejado para a posicao [" << j << "] (Combustivel baixo)" << std::endl;
                            }
                            fila.moveTo(i, j);
                            trocou = true;
                            break;
                        }
                    }
                }
                if (trocou == false) {
                    if (v)
                        std::cout << "Nao foi possivel fazer o remanejamento do " << aviaoI->getID() << " e o voo foi encaminhado para outro aeroporto" << std::endl;
                    fila.remove(i);
                    int evento = aviaoI->getEvento();
                    aeroporto.decrementQueue(evento);
                }
            }
        }
        if (aviaoI->getEvento() == 1) { // DECOLAGEM
            if (aviaoI->getEmergencia() == false && aviaoI->getTnf() > 0.1 * aviaoI->getTev()) {
                aviaoI->setEmergency();
                int j = fila.size()-1;
                while (fila.at(j)->getEmergencia()) { // checa o topo da fila ate achar o primeiro que nao seja emergencia
                    j--;
                }
                if (v)
                    std::cout << "o aviao " << aviaoI->getID() << " ja esperou demais e foi colocado no comeco da fila" << std::endl;
                fila.moveTo(i, j);
            }
        }
    }
}
void updateEstimates(LinkedList<Aviao>& fila, Aeroporto& aeroporto) {
    int npousos = 0;
    int ndecolagens = 0;
    for (int i = fila.size()-1; i >= 0; i--) { 
        Aviao* aviao = fila.at(i);
        aviao->setEst(aeroporto.estimador(aviao->getEvento(), npousos, ndecolagens));
        if (aviao->getEvento() == 1)
            ndecolagens++;
        else
            npousos++;
    }
}
void useLanes(LinkedList<Aviao>& fila, Aeroporto& aeroporto, int& nTotalEmerg, int& tempoTotalEsperaD, int& nTotalD, int& nTotalP, int& tempoTotalEsperaP, int& qtdTotalCombustivel, bool v) {
    // uso das pistas até que não haja nenhum avião na fila ou não haja pista disponível
    // pega o primeiro
    // tenta useAvailable()
    // se não der, pega o seguinte
    int idx = fila.size()-1;
    while (fila.size() > 0 && aeroporto.existsAvailable() && idx >= 0) { 
        Aviao* aviao = fila.at(idx);
        int pistaDisponivel = aeroporto.useAvailable(*aviao, v);
        if (pistaDisponivel != -1) {
            Aviao* aviao = fila.remove(idx);
            if (aviao->getEmergencia())
                nTotalEmerg++;
            int evento = aviao->getEvento();
            aeroporto.decrementQueue(evento);
            if (evento == 1) {
                tempoTotalEsperaD = tempoTotalEsperaD + aviao->getTnf();
                nTotalD++;
            }
            else {
                tempoTotalEsperaP = tempoTotalEsperaP + aviao->getTnf();
                qtdTotalCombustivel = qtdTotalCombustivel + aviao->getCombustivel();
                nTotalP++;
            }
        }
        idx--;
    }
}
void printSummary(LinkedList<Aviao>& fila, int nTotalEmerg, int tempoTotalEsperaD, int nTotalD, int nTotalP, int tempoTotalEsperaP, int qtdTotalCombustivel) {
    int totalComb = 0; // total de combustivel dos avioes esperando para pousar
    int n_pousos = 0; // n de avioes esperando para pousar
    for (int i = fila.size()-1; i >= 0; i--) { // atualiza as estimativas 
        if (fila.at(i)->getEvento() == 0) {
            totalComb = totalComb + fila.at(i)->getCombustivel();
            n_pousos++;
        }
    }
    if (nTotalD > 0) {
        std::cout << "Tempo medio de espera para decolagem: " << static_cast<float>(tempoTotalEsperaD) / nTotalD << std::endl;
    } 
    if (nTotalP > 0) {
        std::cout << "Tempo medio de espera para pouso: " << static_cast<float>(tempoTotalEsperaP) / nTotalP << std::endl;
    } 
    if (n_pousos > 0)
        std::cout << "Qtd media de combustivel dos avioes esperando para pousar: " << static_cast<float>(totalComb) / n_pousos << std::endl;
    if (nTotalP > 0) {
        std::cout << "Qtd media de combustivel disponivel dos avioes que pousaram: " << static_cast<float>(qtdTotalCombustivel) / nTotalP << std::endl;
    }
    std::cout << "TOTAIS" << std::endl;
    std::cout << "# Pousos realizados: " << nTotalP << std::endl;
    std::cout << "# Decolagens realizadas: " << nTotalD << std::endl;
    std::cout << "# de pousos/decolagens de emergencia: " << nTotalEmerg << std::endl;

    printf("\n\n");
}