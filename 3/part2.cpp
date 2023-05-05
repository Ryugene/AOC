#include <bits/stdc++.h>

using namespace std;

char commonchar(string w1, string w2, string w3) {
    char r;
    for (int i = 0; i < w1.size(); ++i) {
        for (int j = 0; j < w2.size(); ++j) {
            for (int k = 0; k < w3.size(); ++k) {
                if (w1.at(i) == w2.at(j) && w2.at(j) == w3.at(k)) {
                    r = w1.at(i);
                    return r;
                }
            }
        }
    }
    return r;
}

int main() {
    ifstream s("input.txt");
    string line;
    string w1;
    string w2;
    string w3;
    int sum = 0;
    int n = 0;
    while(getline(s,line)) {
        ++n;
        if (n % 3 == 1)
            w1 = line;
        else if (n % 3 == 2)
            w2 = line;
        else {
            w3 = line;
            char c = commonchar(w1,w2,w3);
            if (int(c) >= 97  && int(c) <= 122)
                sum += int(c) - 96;
            else
                sum += int(c) - 64 + 26;
        }
        
        
    }
    cout << sum;
}