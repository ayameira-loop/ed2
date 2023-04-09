#include <iostream>
#include <string>
#include <cstdlib>
#include "VetorDinamicoOrdenado.h"

int main() {
    VetorDinamicoOrdenado<std::string, int> vdo;

    std::cout << "primeiro" << std::endl;
    vdo.add("ao", 1);
    //vdo.show();

    std::cout << "segundo" << std::endl;
    vdo.add("roeu", 2);
    //vdo.show();

    std::cout << "terceiro" << std::endl;
    vdo.add("as", 3);
    //vdo.show();

    std::cout << "quarto" << std::endl;
    vdo.add("frias", 4);
    vdo.show();

    std::cout << "quint" << std::endl;
    vdo.add("carnes", 5);
    vdo.show();

    //std::cout << "valor do primeiro: " << vdo.value(1) << std::endl;
    //std::cout << "valor do meio: " << vdo.value(3) << std::endl;
    //std::cout << "valor do ultimo: " << vdo.value(6) << std::endl;

    return 0;
}

