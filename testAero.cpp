#include <iostream>
#include <string>
#include "Aeroporto.h"

int main() {
    Aeroporto aeroporto;

    std::cout << "Checking initial availability: " << std::boolalpha << aeroporto.checkAvailable() << std::endl;

    aeroporto.updateLane(1);
    std::cout << "After updating lane 1: " << std::boolalpha << aeroporto.checkAvailable() << std::endl;

    aeroporto.updateLane(2);
    std::cout << "After updating lane 2: " << std::boolalpha << aeroporto.checkAvailable() << std::endl;

    aeroporto.updateLane(3);
    std::cout << "After updating lane 3: " << std::boolalpha << aeroporto.checkAvailable() << std::endl;

    aeroporto.printStatus();

    return 0;
}
