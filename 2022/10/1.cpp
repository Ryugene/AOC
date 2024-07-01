#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream f("input.txt");
    string line;
    int x = 1;
    int cycle = 0;
    int res = 0;
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
    while(!q.empty()) {
        if (q.front().first == 0) {
            x += q.front().second;
            q.pop();
        }
        --q.front().first;
        ++cycle;
        if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220) {
            res += cycle*x;
        }
    }
    cout << res;
}