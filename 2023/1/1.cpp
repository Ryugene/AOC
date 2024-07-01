#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream f("input.txt");
    string line;
    char n1, n2;
    int res = 0;
    while (getline(f, line)) {
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] >= '0' && line[i] <= '9') {
                n1 = line[i];
                break;
            }
        }
        for (int i = line.size()-1; i >= 0; --i) {
            if (line[i] >= '0' && line[i] <= '9') {
                n2 = line[i];
                break;
            }
        }
        int n = 10*(n1 - '0') + n2 - '0';
        res += n;
    }
    cout << res;
}