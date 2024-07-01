#include <bits/stdc++.h>

using namespace std;

void fillgrid(string line, vector<vector<int>>& grid) {
    size_t i = 0;
    int x;
    int y;
    pair<int, int> p(0, 0);
    while (i < line.size()) {
        if (i < line.size() && line[i] >= '0' && line[i] <= '9') {
            size_t t = i;
            x = stoi(line.substr(i), &t);
            i += t+1;
            y = stoi(line.substr(i), &t);
            i += t;
            if (p.first != 0) {
                if (p.first == y) {
                    for (int j = 0; j <= abs(p.second - x); ++j) {
                        if (p.second - x > 0)
                            grid[y][x + j] = 1;
                        else
                            grid[y][x - j] = 1;
                    }
                }
                else {
                    for (int j = 0; j <= abs(p.first - y); ++j) {
                        if (p.first - y > 0)
                            grid[y + j][x] = 1;
                        else
                            grid[y - j][x] = 1;
                    }
                }
            }
            p = make_pair(y, x);
        }
        else
            i += 4;
    }
}

bool fall_stop(vector<vector<int>>& grid) {
    int s_y = 0;
    int s_x = 500;
    while(grid[s_y+1][s_x-1] == 0 || grid[s_y+1][s_x] == 0 || grid[s_y+1][s_x+1] == 0) {
        if (s_y > 160) {
            return true;
        }
        if (grid[s_y+1][s_x] == 0)
            ++s_y;
        else if (grid[s_y+1][s_x-1] == 0) {
            ++s_y;
            --s_x;
        }
        else {
            ++s_y;
            ++s_x;
        }
    }
    grid[s_y][s_x] = 1;
    return false;
}

int main() { // y [13,160] x [482,556]
    ifstream f("input.txt");
    string line;
    int counter = 1;
    vector<vector<int>> grid(170);
    for (int i = 0; i < grid.size(); ++i) {
        grid[i].resize(600);
    }
    while (getline(f, line)) {
        fillgrid(line, grid);
    }
    int res = 0;
    while(!fall_stop(grid)) {
        ++res;
    }
    cout << res;
}