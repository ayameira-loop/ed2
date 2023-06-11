#include <iostream>
#include <string>

int findLargestMatchingSubst(std::string& first, std::string& second, int k) {
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

int main() {
    std::string first = "abcdef";
    std::string second = "defxyz";

    int k = 2;

    int result = findLargestMatchingSubst(first, second, k);

    std::cout << "Integer result: " << result << std::endl;

    return 0;
}
