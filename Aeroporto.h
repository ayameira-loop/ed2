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
    int npousos;
    int ndecolagens;
    void printEvento(int lane, std::string id, int evento) {
        std::cout << "A pista " << lane << " foi utilizada para " << (evento ? "Decolagem" : "Pouso") << " do voo " << id << std::endl;
    }
    
public:
    Aeroporto() {
        npousos = 0;
        ndecolagens = 0;
        p1 = {0, {0, 1}};
        p2 = {0, {0, 1}};
        p3 = {0, {1}}; // pouso só em emergência
    }
    ~Aeroporto() {}
    void incrementQueue(int evento) {
        if (evento == 1)
            ndecolagens++;
        else
            npousos++;
    }
    void decrementQueue(int evento) {
        if (evento == 1)
            ndecolagens--;
        else
            npousos--;
    }
    bool checkAvailable(int evento) {
        if (evento == 1) // decolagem
            return (p1.status % 4 == 0 || p2.status % 4 == 0 || p3.status % 4 == 0);
        else
            return (p1.status % 4 == 0 || p2.status % 4 == 0);
    }
    int useAvailable(Aviao aviao) {
        std::string id = aviao.getID();
        int evento = aviao.getEvento();
        bool ehEmergencia = aviao.getEmergencia();

        if (evento == 1) { // Decolagem
            if (p1.status % 4 == 0) {
                p1.status++;
                printEvento(1, id, evento);
                return 1;
            } else if (p2.status % 4 == 0) {
                p2.status++;
                printEvento(2, id, evento);
                return 2;
            } else if (p3.status % 4 == 0) {
                p3.status++;
                printEvento(3, id, evento);
                return 3;
            }
        }
        if (evento == 0) { // Pouso
            if (p1.status % 4 == 0) {
                p1.status++;
                printEvento(1, id, evento);
                return 1;
            } else if (p2.status % 4 == 0) {
                p2.status++;
                printEvento(2, id, evento);
                return 2;
            }
        }
        if (ehEmergencia) {
            if (p3.status % 4 == 0) {
                p3.status++;
                std::cout << "EMERGENCIA" << std::endl;
                printEvento(3, id, evento);
                return 3;
            }
        }
        return -1;
    }
    std::string getStatus(Pista p) {
        switch (p.status % 4) {
            case 0:
                return "livre";
            case 1:
                return "em uso";
            case 2:
                return "manutencao (1)";
            case 3:
                return "manutencao (2)";
        }
    }
    void printStatus() {
        // Implementation of printStatus function
        std::cout << "Fila de decolagem: " << ndecolagens << std::endl;
        std::cout << "Fila de pouso: " << npousos << std::endl;
        std::cout << "Pista 1: " << getStatus(p1) << std::endl;
        std::cout << "Pista 2: " << getStatus(p2) << std::endl;
        std::cout << "Pista 3: " << getStatus(p3) << std::endl;
    }
    void updateStatusPistas() {
        if (p1.status % 4 != 0) 
            p1.status++;
        if (p2.status % 4 != 0) 
            p2.status++;
        if (p3.status % 4 != 0) 
            p3.status++;
    }
    int estimador(int evento) {
        int temp1 = p1.status;
        int temp2 = p2.status;
        int temp3 = p3.status;
        int np = npousos;
        int nd = ndecolagens;
        int est = 0;
        while (np > 0 || nd > 0) {
            if (np > 0) {
                if (temp1 % 4 == 0) {
                    temp1++;
                    np--;
                } else if (temp2 % 4 == 0) {
                    temp2++;
                    np--;
                }                
            }
            if (nd > 0) {
                if (temp1 % 4 == 0) {
                    temp1++;
                    nd--;
                } else if (temp2 % 4 == 0) {
                    temp2++;
                    nd--;
                } else if (temp3 % 4 == 0) {
                    temp3++;
                    nd--;
                }                
            }
            est++;
            if (temp1 % 4 != 0) 
                temp1++;
            if (temp2 % 4 != 0) 
                temp2++;
            if (temp3 % 4 != 0) 
                temp3++;
        }
        return est+3;
    }
};
#endif
