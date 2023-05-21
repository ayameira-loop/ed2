#include <iostream>
#include <string>
#include "23Tree.h"

int main() {
    A23<int, std::string> arvore;
    
    arvore.add(10, "10");
    arvore.add(6, "6");
    arvore.add(3, "3");
    arvore.add(15, "15");
    arvore.add(7, "7");

    arvore.print();
    return 0;
}