#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Aviao.h"
#include "Aeroporto.h"


int main() {
    int evento = 1;

    std::cout << (evento ? "Decolagem" : "Pouso") << std::endl;

    return 0;
}