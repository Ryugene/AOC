#include <bits/stdc++.h>

using namespace std;

int score(vector<vector<char>>& grid, int y, int x) {
    int left = 0;
    int right = 0;
    int up = 0;
    int down = 0;
    for (int dx = x-1; dx >= 0; --dx) {
        if (grid[y][dx] < grid[y][x]) {
            ++left;
        }
        else {++left; break;}
    }
    for (int dx = x+1; dx < grid[y].size(); ++dx) {
        if (grid[y][dx] < grid[y][x]) {
            ++right;
        }
        else {++right; break;}
    }
    for (int dy = y-1; dy >= 0; --dy) {
        if (grid[dy][x] < grid[y][x]) {
            ++up;
        }
        else {++up; break;}
    }
    for (int dy = y+1; dy < grid.size(); ++dy) {
        if (grid[dy][x] < grid[y][x]) {
            ++down;
        }
        else {++down; break;}
    }
    return (left * right * up * down);
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
            res = max(res,score(grid,y,x));
        }
    }
    cout << res;
}