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

void connect(pair<int,int> head, pair<int,int>& tail) {
    int hy = head.first;
    int hx = head.second;
    int ty = tail.first;
    int tx = tail.second;
    if ((hy == ty-2 && hx == tx-2) || (hy == ty-2 && hx == tx-1) || (hy == ty-1 && hx == tx-2) ) {
        tail.first = tail.first-1;
        tail.second = tail.second-1;
    }
    else if ((hy == ty-2 && hx == tx+2) || (hy == ty-2 && hx == tx+1) || (hy == ty-1 && hx == tx+2)) {
        tail.first = tail.first-1;
        tail.second = tail.second+1;
    }
    else if ((hy == ty+1 && hx == tx-2) || (hy == ty+2 && hx == tx-2) || (hy == ty+2 && hx == tx-1)) {
        tail.first = tail.first+1;
        tail.second = tail.second-1;
    }
    else if ((hy == ty+1 && hx == tx +2) || (hy == ty+2 && hx == tx+1) || (hy == ty+2 && hx == tx+2)) {
        tail.first = tail.first+1;
        tail.second = tail.second+1;
    }
    else if (hy == ty-2)
        tail.first = tail.first-1;
    else if (hy == ty+2)
        tail.first = tail.first+1;
    else if (hx == tx-2)
        tail.second = tail.second-1;
    else if (hx == tx+2)
        tail.second = tail.second+1;

}

int main() {
    ifstream f("input.txt");
    string line;
    int len = 10000;
    vector<vector<int>> grid(len);
    for (int i = 0; i < len; ++i) {
        grid[i].resize(len);
    }
    vector<pair<int,int>> snake(10);
    for (int i = 0; i < 10; ++i) {
        snake[i] = (make_pair(5000,5000));
    }
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
            snake[0].first += dy;
            snake[0].second += dx;
            for (int t = 0; t < 9; ++t) {
                if (!tailclose(snake[t],snake[t+1])) {
                    connect(snake[t],snake[t+1]);
                    if (t == 8 && grid[snake[t+1].first][snake[t+1].second] == 0) {
                        ++res;
                        grid[snake[t+1].first][snake[t+1].second] = 1;
                    }
                }
                else break;
            }
        }
    }
    cout << res;
}