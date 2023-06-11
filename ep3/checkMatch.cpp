#include <iostream>
#include <string>

bool checkMatch(std::string& first, std::string& second, int k) {
    std::string firstSuffix = first.substr(first.length() - k, k);
    std::string secondPrefix = second.substr(0, k);

    return firstSuffix == secondPrefix;
}

void myCheckMatch(std::string& first, std::string& second, int k) {
    bool match = true;
    int i = k;
    while (match && i < first.length()-1 && i < second.length() - 1) {
        std::string firstSuffix = first.substr(first.length() - i, i);
        std::string secondPrefix = second.substr(0, i);
        std::cout << "comparing " << firstSuffix << " and " << secondPrefix << std::endl;
        match = firstSuffix == secondPrefix;
        if (match) i++;
    }
    std::cout << i << std::endl;
    return;
}

int main() {
    std::string first = "abcdef";
    std::string second = "defxyz";

    int k = 2;

    if (checkMatch(first, second, k)) {
        std::cout << "The first " << k << " characters of the second string match the last " << k << " characters of the first string." << std::endl;
    } else {
        std::cout << "The first " << k << " characters of the second string do not match the last " << k << " characters of the first string." << std::endl;
    }

    myCheckMatch(first, second, k);

    return 0;
}
