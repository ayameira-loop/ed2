#include <iostream>
#include <string>
#include "23Tree.h"

int main() {
    A23<int, std::string> arvore;
    
    arvore.add(10, "10");
    arvore.add(6, "6");
    arvore.add(3, "3");

    arvore.print();
    return 0;
}