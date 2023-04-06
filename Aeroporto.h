#include "Aviao.h"
#ifndef AEROPORTO_H
#define AEROPORTO_H

class Aeroporto {
private:
    struct Pista {
        int status;
        int eventos[2]; // 0: pouso, 1: decolagem
    };
    Pista p1;
    Pista p2;
    Pista p3;
    void printEvento(int lane, std::string id) {
        std::cout << "A pista " << lane << " foi utilizada pelo voo " << id << std::endl;
    }
    
public:
    Aeroporto() {
        Pista p1 = {0, {0, 1}};
        Pista p2 = {0, {0, 1}};
        Pista p3 = {0, {1}}; //
    }
    ~Aeroporto() {}
    bool checkAvailable() {
        return (p1.status % 3 == 0 || p2.status % 3 == 0 || p3.status % 3 == 0);
    }
    int useAvailable(Aviao aviao) {
        std::string id = aviao.getID();
        int evento = aviao.getEvento();
        bool ehEmergencia = aviao.getEmergencia();

        if (evento == 1) { // Pouso
            if (p1.status % 3 == 0) {
                p1.status++;
                printEvento(1, id);
                return 1;
            } else if (p2.status % 3 == 0) {
                p2.status++;
                printEvento(2, id);
                return 2;
            } else if (p3.status % 3 == 0) {
                p3.status++;
                printEvento(3, id);
                return 3;
            }
        }
        if (evento == 0) { // Decolagem
            if (p1.status % 3 == 0) {
                p1.status++;
                printEvento(1, id);
                return 1;
            } else if (p2.status % 3 == 0) {
                p2.status++;
                printEvento(2, id);
                return 2;
            }
        }
        if (ehEmergencia) {
            if (p3.status % 3 == 0) {
                p3.status++;
                std::cout << "EMERGENCIA" << std::endl;
                printEvento(3, id);
                return 3;
            }
        }
        return -1;
    }
    std::string getStatus(Pista p) {
        switch (p.status % 3) {
            case 0:
                return "livre";
            case 1:
                return "manutencao (1)";
            case 2:
                return "manutencao (2)";
        }
    }
    void printStatus() {
        // Implementation of printStatus function
        std::cout << "Status das pistas:" << std::endl;
        std::cout << "Pista 1: " << getStatus(p1) << std::endl;
        std::cout << "Pista 2: " << getStatus(p2) << std::endl;
        std::cout << "Pista 3: " << getStatus(p3) << std::endl;
    }
    void updateStatus() {
        if (p1.status % 3 != 0) 
            p1.status++;
        if (p2.status % 3 != 0) 
            p2.status++;
        if (p3.status % 3 != 0) 
            p3.status++;
    }
};
#endif
