#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream f("input.txt");
    string line;
    int x = 1;
    int cycle = 1;
    int pos = 0;
    queue<pair<int,int>> q; //cycle , value
    while (getline(f,line)) {
        if (line[0] == 'n') {
            q.emplace(make_pair(1,0));
        }
        else if (line[0] == 'a') {
            int val = stoi(line.substr(5));
            q.emplace(make_pair(2,val));
        }
    }
    for (cycle; cycle <= 240; ++cycle) {
        if (q.front().first == 0) {
            x += q.front().second;
            q.pop();
        }
        --q.front().first;
        if (pos == x-1 || pos == x || pos == x+1)
            cout << "#";
        else
            cout << ".";
        ++pos;
        if (cycle % 40 == 0 && cycle != 0) {
            pos = 0;
            cout << endl;
        }
    }
}