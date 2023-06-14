#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include "Graph.h"

std::string generateDNAString(int N) {
    /* Function to generate random DNA strings of length N */
    std::string dnaString;
    char letters[] = {'A', 'G', 'C', 'T'};
    int numLetters = sizeof(letters) / sizeof(letters[0]);

    for (int i = 0; i < N; i++) {
        int randomNum = rand() % numLetters;
        dnaString += letters[randomNum];
    }

    return dnaString;
}

void breakIntoChunks(const std::string& word, const std::vector<int>& startOfChunks, const std::vector<int>& endOfChunks, std::vector<std::string>& chunks) {
    /* Function to break DNA string into chunks */ 
    for (int i = 0; i < startOfChunks.size(); i++) {
        int start = startOfChunks[i];
        int end = endOfChunks[i];
        std::string chunk = word.substr(start, end - start + 1);
        chunks.push_back(chunk);
    }
}

int findLargestMatchingSubst(std::string& first, std::string& second) {
    /* Function to find how many letters of the end of the first string can match with the beginning of the second string. 
       Returns highest match possible */
    int i = 0;
    int highestK = 0;
    while (i < first.length()-1 && i < second.length() - 1) {
        std::string firstSuffix = first.substr(first.length() - i, i);
        std::string secondPrefix = second.substr(0, i);
        if (firstSuffix == secondPrefix)    highestK = i;
        i++;
    }
    return highestK;
}

int main(int argc, char* argv[]) {
    srand(time(0));
    //srand(1234);

    if (argc < 5) {
        std::cout << "Usage: dna <N> <meanChunkSize> <variation> <k>\n";
        return 1;
    }

    int N = std::atoi(argv[1]); // Length of DNA string
    int meanChunkSize = std::atoi(argv[2]); // Mean chunk length
    int variation = std::atoi(argv[3]); // Variation
    int k = std::atoi(argv[4]);

    std::vector<int> startOfChunks(0);
    std::vector<int> endOfChunks(0);

    std::cout << "Breaking DNA string into chunks:\n";

    int start = 0;
    int end = 0;
    int step = 0;

    while (start < N-1 && end < N-1) {
        start = end - step; // Goes back about half of what it moved forward 
        if (start < 0)  start = end + step;
        step = (meanChunkSize + (rand() % variation+1))/2;
        if (start > N-1)    continue;
        startOfChunks.push_back(start);
        int signal = (rand() % 2) * 2 - 1;
        int chunkSize = meanChunkSize + (rand() % variation+1) * signal;
        if (start + chunkSize > N-1)
            chunkSize = (N-1) - start; 
        end = start + chunkSize;
        endOfChunks.push_back(end);
    }
    
    std::string dnaString = generateDNAString(N);
    std::cout << "Generated DNA string:\n" << dnaString << std::endl;

    std::vector<std::string> chunks(0);

    std::cout << "\nBreaking DNA string into chunks:\n";
    breakIntoChunks(dnaString, startOfChunks, endOfChunks, chunks);
    
    int V = chunks.size();

    Graph G(V);
    std::cout << "Number of vertices: " << V << std::endl;
    for (int i = 0; i < chunks.size(); i++) {
        G.setVertexValue(i, chunks[i]);
    }

    for (int i = 0; i < chunks.size(); i++) {
        for (int j = i+1; j < chunks.size(); j++) {
            int L = findLargestMatchingSubst(chunks[i], chunks[j]);
            if (L >= k) {
                G.addEdge(i, j, L);
            }
        }
    }

    // Is it cyclic?
    std::cout << "Cycle?" << std::endl;
    std::cout << G.isCyclic() << std::endl;
    //G.printGraph();

    if (G.isCyclic()) {
        G.makeAcyclic();
        std::cout << "Cycle?" << std::endl;
        std::cout << G.isCyclic() << std::endl;
        //G.printGraph();
    }

    std::cout << "Finding highest weight path" << std::endl;

    std::vector<int> path = G.findHighestWeightPath();

    int prev = -1;
    std::string reconstructedDNA = "";

    for (int vertex : path) {
        if (prev != -1)
            reconstructedDNA = reconstructedDNA + G.getValueAt(vertex).substr(G.getWeight(prev,vertex));
        else
            reconstructedDNA = reconstructedDNA + G.getValueAt(vertex);
        prev = vertex;
    }

    std::cout << reconstructedDNA << std::endl;


    return 0;
}

