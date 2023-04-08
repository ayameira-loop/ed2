#include <iostream>
#include <string>
#include <cstdlib>
#include "Aviao.h"
#include "LinkedList.h"
#include "Aeroporto.h"

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

void addNewPlanes(int k, LinkedList<Aviao>& fila, Aeroporto& aeroporto, int C, int V, float pe, float pp) {
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
    if (v)
        aeroporto.printStatus(v);
    if (vv) {
        for (int i = fila.size()-1; i >= 0; i--) {
            std::cout << i << " - ";
            fila.at(i)->printInfo();
        }
    }
}

void treatExceptions(LinkedList<Aviao>& fila, Aeroporto& aeroporto, bool v, bool vv) {
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
int main() {
    int T = 50; // unidades de tempo de simula ̧c ̃ao;
    int K = 4; // n ́umero m ́aximo de avi ̃oes que chegam no aeroporto em cada unidade de tempo;
    float pp = 0.1;// probabilidade de ser um pouso;
    float pd = 1 - pp;// probabilidade de ser decolagem (1.0 − pp);
    int pe = 0.03; // probabilidade de ser emergˆencia;
    int C = 20; // tempo m ́aximo de combust ́ıvel de um avi ̃ao que deseja pousar;
    int V = 100; // tempo m ́aximo de voo de uma decolagem.

    srand(123);

    int tempoTotalEsperaP = 0;
    int tempoTotalEsperaD = 0;
    int qtdTotalCombustivel = 0;
    int nTotalD = 0;
    int nTotalP = 0;
    int nTotalEmerg = 0;

    LinkedList<Aviao> fila;
    Aeroporto aeroporto;

    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int k = 5;
    bool verbose = true;
    bool veryVerbose = true; 

    addNewPlanes(100, fila, aeroporto, C, V, pe, pp);



    printAllStatus(fila, aeroporto, verbose, veryVerbose);

    

    /*
    addNewPlanes(k, fila, aeroporto, C, V, pe);
    std::cout << "ANTES" << std::endl;
    printAllStatus(fila, aeroporto, verbose, veryVerbose);

    useLanes(fila, aeroporto, nTotalEmerg, tempoTotalEsperaD, nTotalD, nTotalP, tempoTotalEsperaP, qtdTotalCombustivel, verbose);
    std::cout << "DEPOIS" << std::endl;
    printAllStatus(fila, aeroporto, verbose, veryVerbose);

    std::cout << "tempoTotalEsperaP: " << tempoTotalEsperaP << std::endl;
    std::cout << "tempoTotalEsperaD: " << tempoTotalEsperaD << std::endl;
    std::cout << "qtdTotalCombustivel: " << qtdTotalCombustivel << std::endl;
    std::cout << "nTotalD: " << nTotalD << std::endl;
    std::cout << "nTotalP: " << nTotalP << std::endl;
    std::cout << "nTotalEmerg: " << nTotalEmerg << std::endl;
    */

    
    
    
    
    
    


}

