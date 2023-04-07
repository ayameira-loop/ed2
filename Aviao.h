#ifndef AVIAO_H
#define AVIAO_H

class Aviao {
    private:
        std::string id;
        int combustivel;
        int tev; // tempo estimado de voo
        int tnf; // tempo na fila
        int est; // estimativa de espera
        int estIni; // estimativa de espera
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
            tnf = 0;
            est = 0;
            estIni = 0;
            ehEmergencia = (static_cast<double>(std::rand()) / RAND_MAX) <= pe;
            evento = rand() % 2;
        }
        void printInfo() {
            std::cout << "ID: " << id << " | " << "Combustivel: " << combustivel << " | " << "TEV: " << tev << " | " << "Emergencia: " << (ehEmergencia ? "Sim" : "Nao") << " | " << "Evento: " << (evento ? "Decolagem" : "Pouso") << " | TNF: " << tnf << " | EST: " << est << " | ESTINI: " << estIni << std::endl;
            //std::cout << "ID: " << id << std::endl;
            //std::cout << "Combustivel: " << combustivel << std::endl;
            //std::cout << "Tempo Estimado de Voo: " << tev << std::endl;
            //std::cout << "Emergencia: " << (ehEmergencia ? "Sim" : "Nao") << std::endl;
            //std::cout << "Evento: " << (evento ? "Decolagem" : "Pouso") << "\n" << std::endl;
        }
        std::string getID() {
            return id;
        }
        int getEvento() {
            return evento;
        }
        int getEst() {
            return est;
        }
        int getTnf() {
            return tnf;
        }
        int getCombustivel() {
            return combustivel;
        }
        bool getEmergencia() {
            return ehEmergencia;
        }
        void atualizaCombustivel() {
            tnf++;
            combustivel--;
        }
        void setEst(int estimativa) {
            est = estimativa;
        }
        void setEstIni(int estimativa) {
            estIni = estimativa;
        }
};
#endif