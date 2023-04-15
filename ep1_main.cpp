#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include "LinkedList.h"
#include "Aviao.h"
#include "Aeroporto.h"

#define SEED 123

void addNewPlanes(int k, LinkedList<Aviao>& fila, Aeroporto& aeroporto, int C, int V, float pe, float pp);
void printAllStatus(LinkedList<Aviao>& fila, Aeroporto& aeroporto, bool v, bool vv);
void treatExceptions(LinkedList<Aviao>& fila, Aeroporto& aeroporto, bool v, bool vv);
void updateEstimates(LinkedList<Aviao>& fila, Aeroporto& aeroporto);
void useLanes(LinkedList<Aviao>& fila, Aeroporto& aeroporto, int& emergenciaIt, int& nTotalEmerg, int& tempoTotalEsperaD, int& nTotalD, int& nTotalP, int& tempoTotalEsperaP, int& qtdTotalCombustivel, bool v);
void printSummary(LinkedList<Aviao>& fila, Aeroporto aeroporto, int emergenciaIt, int nTotalEmerg, int tempoTotalEsperaD, int nTotalD, int nTotalP, int tempoTotalEsperaP, int qtdTotalCombustivel);

int main(int argc, char* argv[]) {
    // [T, K, pp, pe, C, V, verbose, veryVerbose]
    // 200 2 0 0 75 1000 0 0     
    // ep1 200 2 0 0.05 75 1000 0 0     
    int T;
    int K;
    float pp;
    float pd;
    float pe;
    int C;
    int V;
    int verbose;
    int veryVerbose;
    if (argc == 9) {
        T = atoi(argv[1]);// unidades de tempo de simula ̧c ̃ao;
        K = atoi(argv[2]); // n ́umero m ́aximo de avioes que chegam no aeroporto em cada unidade de tempo;
        pp = atof(argv[3]);// probabilidade de ser um pouso;
        pd = 1 - pp;// probabilidade de ser decolagem (1.0 − pp);
        pe = atof(argv[4]); // probabilidade de ser emergˆencia;
        C = atoi(argv[5]); // tempo m ́aximo de combustivel de um avi ̃ao que deseja pousar;
        V = atoi(argv[6]); // tempo m ́aximo de voo de uma decolagem.
        verbose = atoi(argv[7]);
        veryVerbose = atoi(argv[8]);
    }

    srand(SEED);
    int t = 0;

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
        int emergenciaIt = 0; // conta as emergencias que ocorreram nesta iteração
        if (verbose)
            std::cout << "TEMPO: " << t << " | Adiciona " << k << " aviao(oes)" << "\n\n";

        addNewPlanes(k, fila, aeroporto, C, V, pe, pp);
        treatExceptions(fila, aeroporto, verbose, veryVerbose);
        updateEstimates(fila, aeroporto);
        useLanes(fila, aeroporto, emergenciaIt, nTotalEmerg, tempoTotalEsperaD, nTotalD, nTotalP, tempoTotalEsperaP, qtdTotalCombustivel, verbose);
        updateEstimates(fila, aeroporto);

        // atualiza os valores da iteração (diminui o combustível em uma unidade e incrementa o contador do status das pistas)
        for (int i = fila.size()-1; i >= 0; i--) {
            fila.at(i)->atualizaCombustivel();
        }
        aeroporto.updateStatusPistas();
        t++;
        if (t == T - 1)
            verbose = true;
        if (verbose)
            printSummary(fila, aeroporto, emergenciaIt, nTotalEmerg, tempoTotalEsperaD, nTotalD, nTotalP, tempoTotalEsperaP, qtdTotalCombustivel);
    }

    return 0;
}

void addNewPlanes(int k, LinkedList<Aviao>& fila, Aeroporto& aeroporto, int C, int V, float pe, float pp) {
    // adiciona os novos avioes
    // se for emergencia, coloca na frente da fila
    // se nao, calcula a estimativa de tempo de espera e coloca no final da fila
    for (int i = 0; i < k; i++) {
        Aviao* novoAviao = new Aviao(C, V, pe, pp);
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
    if (v) {
        aeroporto.printStatus(v);
        
    }
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
void useLanes(LinkedList<Aviao>& fila, Aeroporto& aeroporto, int& emergenciaIt, int& nTotalEmerg, int& tempoTotalEsperaD, int& nTotalD, int& nTotalP, int& tempoTotalEsperaP, int& qtdTotalCombustivel, bool v) {
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
            if (aviao->getEmergencia()) {
                nTotalEmerg++;
                emergenciaIt++;
            }
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
    if (v)
        std::cout << std::endl;
}
void printSummary(LinkedList<Aviao>& fila, Aeroporto aeroporto, int emergenciaIt, int nTotalEmerg, int tempoTotalEsperaD, int nTotalD, int nTotalP, int tempoTotalEsperaP, int qtdTotalCombustivel) {
    std::cout << "Fila de pouso: " << aeroporto.getPousos() << std::endl;
    for (size_t i = 0; i < fila.size(); i++)
    {   
        Aviao* aviaoI = fila.at(i);
        if (aviaoI->getEvento() == false)
            aviaoI->printInfo();
    }
    std::cout << std::endl;
    
    std::cout << "Fila de decolagem: " << aeroporto.getDecolagens() << std::endl;
    for (size_t i = 0; i < fila.size(); i++)
    {   
        Aviao* aviaoI = fila.at(i);
        if (aviaoI->getEvento())
            aviaoI->printInfo();
    }
    std::cout << std::endl;
        
    int totalComb = 0; // total de combustivel dos avioes esperando para pousar
    int n_pousos = 0; // n de avioes esperando para pousar
    for (int i = fila.size()-1; i >= 0; i--) { // atualiza as estimativas 
        if (fila.at(i)->getEvento() == 0) {
            totalComb = totalComb + fila.at(i)->getCombustivel();
            n_pousos++;
        }
    }
    if (nTotalP > 0) {
        std::cout << "Tempo medio de espera para pouso: " << static_cast<float>(tempoTotalEsperaP) / nTotalP << std::endl;
    } 
    if (nTotalD > 0) {
        std::cout << "Tempo medio de espera para decolagem: " << static_cast<float>(tempoTotalEsperaD) / nTotalD << std::endl;
    } 
    if (n_pousos > 0)
        std::cout << "Qtd media de combustivel dos avioes esperando para pousar: " << static_cast<float>(totalComb) / n_pousos << std::endl;
    if (nTotalP > 0) {
        std::cout << "Qtd media de combustivel disponivel dos avioes que pousaram: " << static_cast<float>(qtdTotalCombustivel) / nTotalP << std::endl;
    }
    std::cout << "Qtd de avioes pousando/decolando em situacao de emergencia: " << emergenciaIt << std::endl;

    std::cout << "\n" << "TOTAIS:" << std::endl;
    std::cout << "# Pousos realizados: " << nTotalP << std::endl;
    std::cout << "# Decolagens realizadas: " << nTotalD << std::endl;
    std::cout << "# de pousos/decolagens de emergencia: " << nTotalEmerg << std::endl;

    printf("\n\n");
}