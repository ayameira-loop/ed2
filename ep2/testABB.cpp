#include <iostream>
#include <string>
#include "ArvoreBuscaBinaria.h"

int main() {
    ArvoreBuscaBinaria<int, std::string> arvore;
    
    arvore.add(1, "1");
    arvore.add(4, "4");
    arvore.add(2, "2");
    arvore.add(0, "0");
    arvore.add(5, "5");
    arvore.add(3, "3");
    //std::cout << arvore.value(3);

    arvore.print();
    return 0;
}