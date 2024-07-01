#include <bits/stdc++.h>

using namespace std;

bool CheckSurroundings(vector<vector<char>>& grid, int y, int x) {
    for (int dy = -1; dy < 2; ++dy) {
        for (int dx = -1; dx < 2; ++dx) {
            // adjacent is a dot or a digit
            if (y+dy < 0 || y+dy >= grid.size() || x+dx < 0 || x+dx >= grid[y].size() || grid[y+dy][x+dx] == '.' || (grid[y+dy][x+dx] >= '0' && grid[y+dy][x+dx] <= '9')) {
                continue;
            }
            // is a part number
            return true;
        }
    }
    // is not a part number
    return false;
}

int ReadNumber(vector<vector<char>>& grid, int y, int x) {
    int n = 0;
    int dx = 0;
    while (x+dx < grid[y].size() && grid[y][x+dx] >= '0' && grid[y][x+dx] <= '9') {
        n *= 10;
        n += grid[y][x+dx] - '0';
        ++dx;
    }
    return n;
}

int main() {
    vector<vector<char>> grid;
    ifstream f("input.txt");
    string line;
    int ans = 0;
    while (getline(f,line)) {
        vector<char> row;
        for (auto& c : line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] >= '0' && grid[y][x] <= '9') {
                int dx = 0;
                bool part_n = false;
                int n = ReadNumber(grid, y, x);
                string s_n = to_string(n);
                while (x+dx < grid[y].size() && grid[y][x+dx] >= '0' && grid[y][x+dx] <= '9' && !part_n) {
                    part_n = CheckSurroundings(grid, y, x+dx);
                    ++dx;
                }
                if (part_n) {
                    ans += n;
                }
                x += s_n.size() -1;
            }
        }
    }
    cout << ans;
}