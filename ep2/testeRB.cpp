#include <iostream>
#include <string>
#include "RBTree.h"

int main() {
    RBTree<int, std::string> arvore;
    
    std::cout << "adiciona 15" << std::endl;
    arvore.add(15, "15");
    std::cout << "adiciona 10" << std::endl;
    arvore.add(10, "10");
    std::cout << "adiciona 7" << std::endl;
    arvore.add(7, "7");
    std::cout << "adiciona 18" << std::endl;
    arvore.add(18, "18");
    std::cout << "adiciona 25" << std::endl;
    arvore.add(25, "25");
    std::cout << "adiciona 11" << std::endl;
    arvore.add(11, "11");
    std::cout << "adiciona 23" << std::endl;
    arvore.add(23, "23");
    std::cout << "adiciona 29" << std::endl;
    arvore.add(29, "29");
    std::cout << "adiciona 33" << std::endl;
    arvore.add(33, "33");
    //std::cout << arvore.value(3);

    arvore.print();
    return 0;
}