#include <bits/stdc++.h>

using namespace std;

bool visible(vector<vector<char>>& grid, int y, int x) {
    int left = 1;
    int right = 1;
    int up = 1;
    int down = 1;
    for (int dx = x-1; dx >= 0; --dx) {
        if (grid[y][dx] >= grid[y][x]) {
            left = 0; break;
        }
    }
    for (int dx = x+1; dx < grid[y].size(); ++dx) {
        if (grid[y][dx] >= grid[y][x]) {
            right = 0; break;
        }
    }
    for (int dy = y-1; dy >= 0; --dy) {
        if (grid[dy][x] >= grid[y][x]) {
            up = 0; break;
        }
    }
    for (int dy = y+1; dy < grid.size(); ++dy) {
        if (grid[dy][x] >= grid[y][x]) {
            down = 0; break;
        }
    }
    return (left || right || up || down);
}

int main() {
    ifstream f("input.txt");
    string line;
    int res = 0;
    vector<vector<char>> grid;
    while (getline(f,line)) {
        vector<char> row;
        for (char& c : line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (visible(grid,y,x))
                ++res;
        }
    }
    cout << res;
}