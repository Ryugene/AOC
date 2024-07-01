#include <bits/stdc++.h>

using namespace std;

int main() {
    int sum = 0;
    int m1 = 0;
    int m2 = 0;
    int m3 = 0;
    string line;
    ifstream input("input.txt");
    while (getline(input,line)) {
        if (line == "") {
            if (sum > m1) {
                m3 = m2;
                m2 = m1;
                m1 = sum;
            }
            else if (sum <= m1 && sum > m2) {
                m3 = m2;
                m2 = sum;
            }
            else if (sum <= m2 && sum > m3)
                m3 = sum;
            sum = 0;
        }
        else {
            sum += stoi(line);
        }
    }
    cout << m1+m2+m3;
}