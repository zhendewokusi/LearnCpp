#include <iostream>
#include <string>
#include <vector>

using namespace std;

void computeNextBruteForce(int* next, const string& s) {
    int length = s.size();

    for (int i = 0; i < length; i++) {
        int j = 0;  // 将 j 从0开始
        while (j < i) {
            if (s.substr(0, j + 1) == s.substr(i - j, j + 1)) {
                j++;
            } else {
                break;
            }
        }
        next[i] = j + 1;
    }
}

int main() {
    string pattern = "ababcababc";
    int patternLength = pattern.size();
    int next[patternLength];

    computeNextBruteForce(next, pattern);

    cout << "Partial Match Table (Next Array):" << endl;
    for (int i = 0; i < patternLength; i++) {
        cout << "next[" << i << "] = " << next[i] << endl;
    }

    return 0;
}
