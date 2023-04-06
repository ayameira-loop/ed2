#ifndef AVIAO_H
#define AVIAO_H

class Aviao {
    private:
        std::string id;
        int combustivel;
        int tev; // tempo estimado de voo
        bool ehEmergencia;
        int evento; // 0: pouso, 1: decolagem
        std::string generateRandomId() { // %c%c-%d%d%d
            char idChars[7];
            idChars[0] = rand() % 26 + 'A';
            idChars[1] = rand() % 26 + 'A';
            idChars[2] = '-';
            idChars[3] = rand() % 10 + '0';
            idChars[4] = rand() % 10 + '0';
            idChars[5] = rand() % 10 + '0';
            idChars[6] = '\0';
            return std::string(idChars);
        }

    public:
        Aviao(int maxc, int maxv, float pe) {
            id = generateRandomId();
            combustivel = rand() % maxc + 1;
            tev = rand() % maxv + 1;
            ehEmergencia = (static_cast<double>(std::rand()) / RAND_MAX) <= pe;
            evento = rand() % 2;
        }
        void printInfo() {
            std::cout << "ID: " << id << std::endl;
            std::cout << "Combustivel: " << combustivel << std::endl;
            std::cout << "Tempo Estimado de Voo: " << tev << std::endl;
            std::cout << "Emergencia: " << (ehEmergencia ? "Sim" : "Nao") << std::endl;
            std::cout << "Evento: " << (ehEmergencia ? "Decolagem" : "Pouso") << "\n" << std::endl;
        }
        std::string getID() {
            return id;
        }
        int getEvento() {
            return evento;
        }
        bool getEmergencia() {
            return ehEmergencia;
        }
};
#endif