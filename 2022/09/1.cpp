#include <bits/stdc++.h>

using namespace std;

bool tailclose(pair<int,int> head, pair<int,int> tail) {
    for (int dy = -1; dy < 2; ++dy) {
        for (int dx = -1; dx < 2; ++dx) {
            if (tail.first == head.first+dy && tail.second == head.second+dx)
                return true;
        }
    }
    return false;
}

int main() {
    ifstream f("input.txt");
    string line;
    int len = 10000;
    vector<vector<int>> grid(len);
    for (int i = 0; i < len; ++i) {
        grid[i].resize(len);
    }
    pair<int,int> head(5000,5000); // (y,x)
    pair<int,int> tail = head;
    grid[5000][5000] = 1;
    int res = 1;
    while(getline(f,line)) {
        char d = line[0];
        int moves = stoi(line.substr(2));
        int dy = 0;
        int dx = 0;
        if (d == 'U')
            dy = -1;
        else if (d == 'R')
            dx = 1;
        else if (d == 'D')
            dy = 1;
        else
            dx = -1;
        for (int i = 0; i < moves; ++i) {
            head.first += dy;
            head.second += dx;
            if (!tailclose(head,tail)) {
                if (grid[head.first-dy][head.second-dx] == 0)
                    ++res;
                grid[head.first-dy][head.second-dx] = 1;
                tail.first = head.first-dy;
                tail.second = head.second-dx;
            }
        }
    }
    cout << res;
}