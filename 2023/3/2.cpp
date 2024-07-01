#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

ll ReadNumber(vector<vector<char>>& grid, int y, int& x) {
    ll n = 0;
    int dx = 0;
    while (x+dx >= 0 && grid[y][x+dx] >= '0' && grid[y][x+dx] <= '9') {
        --dx;
    }
    ++dx;
    x += dx;
    dx = 0;
    while (x+dx < grid[y].size() && grid[y][x+dx] >= '0' && grid[y][x+dx] <= '9') {
        n *= 10;
        n += grid[y][x+dx] - '0';
        ++dx;
    }
    --dx;
    x += dx;
    return n;
}

ll CheckSurroundings(vector<vector<char>>& grid, int y, int x) {
    int start_y = y;
    int start_x = x;
    vector<ll> nums;
    for (int dy = -1; dy < 2; ++dy) {
        y += dy;
        for (int dx = -1; x <= start_x+1 && dx < 2; ++dx) {
            x += dx;
            // adjacent is a digit
            if (y < 0 || y >= grid.size() || x < 0 || x >= grid[y].size() || (grid[y][x] >= '0' && grid[y][x] <= '9')) {
                ll n = ReadNumber(grid, y, x);
                nums.push_back(n);
                if (x == start_x-1)
                    ++x;
                else if (x == start_x || x == start_x +1)
                    break;
            }
            else
                x = start_x;
        }
        x = start_x;
        y = start_y;
    }
    if (nums.size() == 2)
        return nums[0]*nums[1];
    return 0;
}

int main() {
    vector<vector<char>> grid;
    ifstream f("input.txt");
    string line;
    ll ans = 0;
    while (getline(f,line)) {
        vector<char> row;
        for (auto& c : line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == '*') {
                ll product = CheckSurroundings(grid, y, x);
                ans += product;
            }
        }
    }
    cout << ans;
}