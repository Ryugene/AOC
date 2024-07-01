#include <bits/stdc++.h>

using namespace std;

int main() {
    int sum = 0;
    int m = 0;
    string line;
    ifstream input("input.txt");
    while (getline(input,line)) {
        if (line == "") {
            m = max(sum,m);
            sum = 0;
        }
        else {
            sum += stoi(line);
        }
    }
    cout << m;
}