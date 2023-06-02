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
void breakIntoChunks(const std::string& dnaString, const std::vector<int>& chunkSizes) {
    int startIndex = 0;
    int numChunks = chunkSizes.size();

    for (int i = 0; i < numChunks; i++) {
        int chunkSize = chunkSizes[i];
        std::cout << "Chunk " << i + 1 << ": ";
        for (int j = startIndex; j < startIndex + chunkSize && j < dnaString.length(); j++) {
            std::cout << dnaString[j];
        }
        std::cout << std::endl;
        startIndex += chunkSize;
    }
}

int main() {
    srand(time(0)); // Seed the random number generator

    int N; // Length of DNA string
    std::cout << "Enter the length of the DNA string: ";
    std::cin >> N;

    int meanChunkSize; // Mean chunk size
    std::cout << "Enter the mean chunk size: ";
    std::cin >> meanChunkSize;

    int var; // Variance
    std::cout << "Enter the variance: ";
    std::cin >> var;

    std::vector<int> chunkSizes(0);
    std::cout << "Breaking DNA string into chunks:\n";

    int remaining = N; // How many letters are left in the string (not chunked yet)
    int count = 0;
    while (remaining > 0) {
        int signal = (rand() % 2) * 2 - 1;
        int chunkSize = meanChunkSize + (rand() % var+1) * signal; // Generate random chunk size with variance of -var, 0, or var
        //std::cout << chunkSize << std::endl;
        if (remaining - chunkSize < 0) {
            chunkSize = remaining;
        }
        chunkSizes.push_back(chunkSize);
        remaining = remaining - chunkSize;
    }

    std::string dnaString = generateDNAString(N);
    std::cout << "Generated DNA string: " << dnaString << std::endl;

    std::cout << "\nBreaking DNA string into chunks:\n";
    breakIntoChunks(dnaString, chunkSizes);

    return 0;
}
