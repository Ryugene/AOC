#include <bits/stdc++.h>

using namespace std;

bool overlapinterval(pair<int,int> i1, pair<int,int> i2) {
    if (i1.second < i2.first || i2.second < i1.first)
        return false;
    return true;
}

pair<int,int> parseinput(string in) {
    int n1;
    int n2;
    string n = "";
    int i = 0;
    while (in[i] != '-') {
        n += in[i];
        ++i;
    }
    ++i;
    n1 = stoi(n);
    n = "";
    while (i < in.size()) {
        n += in[i];
        ++i;
    }
    n2 = stoi(n);
    pair<int,int> res(n1,n2);
    return res;
}

int main() {
    ifstream f("input.txt");
    string line;
    int sum = 0;
    while (getline(f,line)) {
        string first;
        string second;
        bool sec = false;
        for (char c : line) {
            if (c != ',' && sec == false)
                first += c;
            else if (c == ',')
                sec = true;
            else
                second += c;
        }
        pair<int,int> i1 = parseinput(first);
        pair<int,int> i2 = parseinput(second);
        if (overlapinterval(i1,i2) || overlapinterval(i2,i1)) {
            sum += 1;
        }
    }
    cout << sum;
}