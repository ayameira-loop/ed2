#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // Get the number of words from user
    int N;
    cout << "Enter the number of words: ";
    cin >> N;

    // Get the words from user
    vector<string> words(N);
    cout << "Enter " << N << " words:" << endl;
    for (int i = 0; i < N; i++) {
        cin >> words[i];
    }

    // Print the words
    cout << "The words are:" << endl;
    for (int i = 0; i < N; i++) {
        cout << words[i] << endl;
    }

    return 0;
}
