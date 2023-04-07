#include <iostream>
#include <string>
#include "Aeroporto.h"

int main() {
    Aeroporto aeroporto;
    aeroporto.incrementQueue(0);
    aeroporto.incrementQueue(0);
    aeroporto.incrementQueue(1);
    aeroporto.incrementQueue(1);
    aeroporto.incrementQueue(1);
    aeroporto.incrementQueue(1);
    aeroporto.incrementQueue(1);
    aeroporto.incrementQueue(1);
    aeroporto.incrementQueue(1);
    aeroporto.printStatus();
    int evento = 0;

    std::cout << aeroporto.estimador(evento) << std::endl;
    aeroporto.printStatus();


    return 0;
}
