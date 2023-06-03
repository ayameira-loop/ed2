#include <iostream>
#include <string>

bool checkMatch(const std::string& first, const std::string& second, int k) {
    if (first.length() < k || second.length() < k) {
        // If either string is shorter than k characters, they can't match
        return false;
    }

    std::string firstSuffix = first.substr(first.length() - k, k);
    std::string secondPrefix = second.substr(0, k);

    return firstSuffix == secondPrefix;
}

int main() {
    std::string first = "abcdef";
    std::string second = "xyzdef";

    int k = 3;

    if (checkMatch(first, second, k)) {
        std::cout << "The first " << k << " characters of the second string match the last " << k << " characters of the first string." << std::endl;
    } else {
        std::cout << "The first " << k << " characters of the second string do not match the last " << k << " characters of the first string." << std::endl;
    }

    return 0;
}
