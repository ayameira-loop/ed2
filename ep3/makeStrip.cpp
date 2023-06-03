#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

// Function to generate random DNA strings of length N
std::string generateDNAString(int N) {
    std::string dnaString;
    static const char letters[] = {'A', 'G', 'C', 'T'};
    int numLetters = sizeof(letters) / sizeof(letters[0]);

    for (int i = 0; i < N; i++) {
        int randomNum = rand() % numLetters;
        dnaString += letters[randomNum];
    }

    return dnaString;
}

// Function to break DNA string into chunks
void breakIntoChunks(const std::string& word, const std::vector<int>& startOfChunks, const std::vector<int>& endOfChunks) {
    for (int i = 0; i < startOfChunks.size(); i++) {
        int start = startOfChunks[i];
        int end = endOfChunks[i];
        std::string chunk = word.substr(start, end - start + 1);
        std::cout << "Chunk " << i + 1 << ": " << chunk << std::endl;
    }
}

int main() {
    srand(time(0)); // Seed the random number generator

    int N; // Length of DNA string
    std::cout << "Enter the length of the DNA string: ";
    std::cin >> N;

    int meanChunkSize; // Mean chunk length
    std::cout << "Enter the mean chunk length: ";
    std::cin >> meanChunkSize;

    int var; // Variance
    std::cout << "Enter the variance: ";
    std::cin >> var;

    std::vector<int> startOfChunks(0);
    std::vector<int> endOfChunks(0);

    std::cout << "Breaking DNA string into chunks:\n";

    int start = 0;
    int end = 0;
    int step = 0;

    while (start < N-1 && end < N-1) {
        start = end - step; // Goes back about half of what it moved forward 
        if (start < 0)  start = end + step;
        step = (meanChunkSize + (rand() % var+1))/2;
        if (start > N-1)    continue;
        startOfChunks.push_back(start);
        int signal = (rand() % 2) * 2 - 1;
        int chunkSize = meanChunkSize + (rand() % var+1) * signal;
        if (start + chunkSize > N-1)
            chunkSize = (N-1) - start; 
        end = start + chunkSize;
        endOfChunks.push_back(end);
    }
    
    std::string dnaString = generateDNAString(N);
    std::cout << "Generated DNA string: " << dnaString << std::endl;

    std::cout << "\nBreaking DNA string into chunks:\n";
    breakIntoChunks(dnaString, startOfChunks, endOfChunks);

    return 0;
}
