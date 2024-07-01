#include <bits/stdc++.h>

using namespace std;

char commonchar(string w1, string w2) {
    char r;
    for (int i = 0; i < w1.size(); ++i) {
        for (int j = 0; j < w2.size(); ++j) {
            if (w1.at(i) == w2.at(j)) {
                r = w1.at(i);
                return r;
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
    int sum = 0;
    while(getline(s,line)) {
        for (int i = 0; i < line.size(); ++i) {
            if (i < line.size()/2) 
                w1 += line[i];
            else
                w2 += line[i];
        }
        char c = commonchar(w1,w2);
        if (int(c) >= 97  && int(c) <= 122)
            sum += int(c) - 96;
        else
            sum += int(c) - 64 + 26;
        w1 = "";
        w2 = "";
    }
    cout << sum;
}