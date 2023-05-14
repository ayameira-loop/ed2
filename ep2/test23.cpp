#include <iostream>
#include <string>
#include "23Tree.h"

int main() {
    A23<int, std::string> arvore;
    
    arvore.add(1, "1");
    arvore.add(4, "4");
    arvore.add(2, "2");
    arvore.add(0, "0");
    arvore.add(5, "5");
    arvore.add(3, "mb");
    std::cout << arvore.value(3);

    arvore.print();
    return 0;
}