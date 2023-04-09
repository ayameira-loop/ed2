#include <string>
#include <unordered_set>
#include <sstream>

class Palavra {
public:
    // Constructor
    Palavra(const std::string palavra) {
        calcularAtributos(palavra);
    }
    Palavra() {
        ocorrencias = 0;
        numLetras = 0;
        numVogaisSemRepeticao = 0;
    }
    void addOcorrencia() {
        ocorrencias++;
    }
    int getOcorrencias() { return ocorrencias; }
    int getNumLetras() { return numLetras; }
    int getNumVogaisSemRepeticao() { return numVogaisSemRepeticao; }

    std::string toString() {
        std::ostringstream oss;
        oss << "{ Ocorrencias: " << ocorrencias << ", ";
        oss << "#Letras: " << numLetras << ", ";
        oss << "#VogaisSR: " << numVogaisSemRepeticao << " }";
        return oss.str();
    }

private:
    int ocorrencias;
    int numLetras;
    int numVogaisSemRepeticao;

    void calcularAtributos(const std::string& palavra) {
        ocorrencias = 1;
        numLetras = palavra.size();
        numVogaisSemRepeticao = calcularNumVogaisSemRepeticao(palavra);  // numero de vogais distintas em uma palavra
    }

    int calcularNumVogaisSemRepeticao(const std::string& palavra) {
        std::string tempPalavra = palavra;
        static std::unordered_set<char> vogais = {'a', 'e', 'i', 'o', 'u'};
        std::unordered_set<char> vogaisEncontradas;
        for (char c : tempPalavra) {
            char lowercaseC = std::tolower(c); // nao quero distinguir entre lowercase e uppercase
            if (vogais.count(lowercaseC)) {
                vogaisEncontradas.insert(lowercaseC);
            }
        }
        return vogaisEncontradas.size();
    }

};
