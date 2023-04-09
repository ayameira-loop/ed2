#include <iostream>
#include <string>
#include "Palavra.h"

int main() {
    
    //int N;
    //std::cin >> N;
    //for (int i = 0; i < N; ++i) {
    //    std::string palavra;
    //    std::cin >> palavra;
    //    Palavra *p = new Palavra(palavra);
    //    std::cout << palavra << " " << p->getOcorrencias() << " " << p->getNumLetras() << " " << p->getNumVogaisSemRepeticao() << std::endl;
    //}

    std::string palavra = "lalola";
    Palavra *p = new Palavra(palavra);
    p->addOcorrencia();
    std::cout << palavra << " " << p->getOcorrencias() << " " << p->getNumLetras() << " " << p->getNumVogaisSemRepeticao() << std::endl;


    return 0;
}
