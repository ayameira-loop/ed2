#include <iostream>
#include <chrono>
// cat .\moreWords | ./crono

int main() {
    std::clock_t start;
    double duration;

    // Start the timer
    start = std::clock();

    // Run the code you want to measure
    int i, count = 0;
    std::string E;
    std::cin >> E;


    // build array with N words
    int N; 
    std::cin >> N;
    std::string words[N];
    for (int i = 0; i < N; i++) {
        std::cout << words[i];
        std::cin >> words[i];
    }


    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    // Print the duration
    std::cout << "Execution time: " << duration << " ms" << std::endl;

    return 0;
}
