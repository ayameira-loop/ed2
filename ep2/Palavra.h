#include <string>
#include <unordered_set>
#include <sstream>

class Palavra {
public:
    Palavra(std::string palavra) {
        calcularAtributos(palavra);
    }
    Palavra() {
        ocorrencias = 0;
        numLetras = 0;
        numVogaisSemRepeticao = 0;
        temLetraRepetida = false;
    }
    void addOcorrencia() {
        ocorrencias++;
    }
    int getOcorrencias() { return ocorrencias; }
    int getNumLetras() { return numLetras; }
    int getNumVogaisSemRepeticao() { return numVogaisSemRepeticao; }
    bool getTemRepetida() { return temLetraRepetida; }

    std::string toString() {
        std::ostringstream oss;
        oss << "{ Ocorrencias: " << ocorrencias << ", ";
        oss << "#Letras: " << numLetras << ", ";
        oss << "#VogaisSR: " << numVogaisSemRepeticao << ", ";
        oss << "Repete Letra: " << temLetraRepetida << " }";
        return oss.str();
    }

    void setOcorrencia(int num) {
        ocorrencias = num;
    }

private:
    int ocorrencias;
    int numLetras;
    int numVogaisSemRepeticao;
    bool temLetraRepetida;

    void calcularAtributos(std::string palavra) {
        ocorrencias = 1;
        numLetras = palavra.size();
        numVogaisSemRepeticao = calcularNumVogaisSemRepeticao(palavra);  // numero de vogais distintas em uma palavra
        temLetraRepetida = repeteLetra(palavra);
    }

    int calcularNumVogaisSemRepeticao(std::string palavra) {
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

    std::string toLowerCase(std::string str) {
        std::string result = str;

        for (char& c : result) {
            c = std::tolower(c);
        }
        return result;
    }

    bool repeteLetra(std::string word) {
        std::string allLowerWord = toLowerCase(word);
        int len = allLowerWord.length();
        for (int i = 0; i < len - 1; i++) {
            for (int j = i + 1; j < len; j++) {
                if (allLowerWord[i] == allLowerWord[j]) {
                    return true;
                }
            }
        }
        return false; 
    }

};
