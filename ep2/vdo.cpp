#include <iostream>
#include <string>
#include <cstdlib>
#include "VetorDinamicoOrdenado.h"

int main() {
    VetorDinamicoOrdenado<int, std::string> vdo;

    std::cout << "primeiro" << std::endl;
    vdo.add(1, "A");
    vdo.show();

    std::cout << "segundo" << std::endl;
    vdo.add(4, "D");
    vdo.show();

    std::cout << "terceiro" << std::endl;
    vdo.add(6, "B");
    vdo.show();

    std::cout << "quarto" << std::endl;
    vdo.add(3, "C");
    vdo.show();

    std::cout << "quinto" << std::endl;
    vdo.add(6, "E");
    vdo.show();

    std::cout << "valor do primeiro: " << vdo.value(1) << std::endl;
    std::cout << "valor do meio: " << vdo.value(3) << std::endl;
    std::cout << "valor do ultimo: " << vdo.value(6) << std::endl;

    return 0;
}

