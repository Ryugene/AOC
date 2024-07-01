#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream f("input.txt");
    string line;
    int n1, n2;
    vector<string> v = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int res = 0;
    while (getline(f, line)) {
        n1 = -1; n2 = -1;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] >= '0' && line[i] <= '9') {
                if (n1 == -1)
                    n1 = int(line[i]) - '0';
                else
                    n2 = int(line[i]) - '0';
            }
            else {
                for (int num = 0; num < v.size(); ++num) {
                    int k = 0;
                    for (int j = i; j < line.size() && k < v[num].size(); ++j) {
                        if (line[j] != v[num][k])
                            break;
                        ++k;
                    }
                    if (k == v[num].size()) {
                        if (n1 == -1)
                            n1 = num+1;
                        else
                            n2 = num+1;
                        break;
                    }
                }
            }
        }
        if (n2 == -1)
            n2 = n1;
        res += 10*n1 + n2;
    }
    cout << res;
}