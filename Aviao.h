class Aviao {
    private:
        std::string id;
        int combustivel;
        int tev; // tempo estimado de voo
        bool ehEmergencia;
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
            ehEmergencia = (rand() % 100 + 1) <= pe;
        }
        void printInfo() {
            std::cout << "ID: " << id << std::endl;
            std::cout << "Combustivel: " << combustivel << std::endl;
            std::cout << "Tempo Estimado de Voo: " << tev << std::endl;
            std::cout << "Emergencia: " << (ehEmergencia ? "Sim" : "Nao") << "\n" << std::endl;
        }
};