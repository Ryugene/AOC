#include <bits/stdc++.h>

using namespace std;

bool travel(vector<vector<int>>& grid, int d_ind, int& y, int& x) { //returns true if we can move after travelling
    int dy = 0; int dx = 0;
    int new_y = y; int new_x = x;
    switch (d_ind) {
    case 0:
        dy = 0; dx = -1; break;
    case 1:
        dy = -1; dx = 0; break;
    case 2:
        dy = 0; dx = 1; break;
    case 3:
        dy = 1; dx = 0; break;
    }
    while (new_y + dy >= 0 && new_y + dy < grid.size() && new_x + dx >= 0 && new_x + dx < grid[new_y + dy].size() && grid[new_y + dy][new_x + dx] != 0) {
        new_y += dy;
        new_x += dx;
    }
    if (grid[new_y][new_x] == 2)
        return false;
    y = new_y; x = new_x;
    return true;
}

void rotate(size_t& i, string& commands, int& d_ind) {
    switch (commands[i]) {
    case 'R':
        d_ind = (d_ind + 1) % 4; break;
    case 'L':
        d_ind = (d_ind + 3) % 4; break;
    }
    ++i;
}

void solve(vector<vector<int>>& grid, int& y, int& x, string& commands, int& d_ind) {
    size_t i = 0;
    vector<pair<int, int>> dirs;
    pair<int, int> d1(0, 1); pair<int, int> d2(1, 0); pair<int, int> d3(0, -1); pair<int, int> d4(-1, 0);
    dirs.push_back(d1); dirs.push_back(d2); dirs.push_back(d3); dirs.push_back(d4);
    while (i < commands.size()) {
        size_t ind = i;
        int steps = stoi(commands.substr(i), &ind); i += ind;
        int dy = dirs[d_ind].first;
        int dx = dirs[d_ind].second;
        for (int j = 0; j < steps; ++j) {
            if (y + dy < 0 || y + dy >= grid.size() || x + dx < 0 || x + dx >= grid[y].size() || grid[y + dy][x + dx] == 0) {
                if (!travel(grid, d_ind, y, x)) break;
            }
            else if (grid[y + dy][x + dx] == 1) {
                y += dy; x += dx;
            }
            else if (grid[y + dy][x + dx] == 2) break;
        }
        if (i < commands.size()) rotate(i, commands, d_ind);
    }
}

int main() {
    ifstream f("input.txt");
    string line;
    vector<vector<int>> grid;
    string commands = "";
    while (getline(f, line)) {
        if (isdigit(line[0])) {
            commands = line; break;
        }
        vector<int> row;
        for (int i = 0; i < 150; ++i) {
            if (i >= line.size() || line[i] == ' ')
                row.push_back(0);
            else if (i < line.size() && line[i] == '.')
                row.push_back(1);
            else row.push_back(2);
        }
        grid.push_back(row);
    }
    int y = 0;
    int x = 50;
    int d_ind = 0;
    solve(grid, y, x, commands,d_ind); ++y; ++x;
    cout << y << " " << x << " " << d_ind;
    int res = 1000*y + 4*x + d_ind;
    cout << " " << res;
}