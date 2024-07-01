#include <bits/stdc++.h>

using namespace std;

bool first_half(vector<vector<int>>& grid, int y, int x) {
    vector<pair<int,int>> dirs;
    dirs.push_back(make_pair(-1,-1)); dirs.push_back(make_pair(-1,0)); dirs.push_back(make_pair(-1,1));
    dirs.push_back(make_pair(0,-1)); dirs.push_back(make_pair(0,1));
    dirs.push_back(make_pair(1,-1)); dirs.push_back(make_pair(1,0)); dirs.push_back(make_pair(1,1));
    for (auto&& p : dirs) {
        int dy = p.first; int dx = p.second;
        if (grid[y+dy][x+dx] == 1) return false;
    }
    return true;
}

void second_half(vector<vector<int>>& grid, int y, int x, map<pair<int,int>,vector<pair<int,int>>>& m, vector<vector<pair<int,int>>>& dirs, bool& call) {
    call = true;
    for (auto&& v : dirs) {
        bool move = true;
        int dy = v[1].first; int dx = v[1].second;
        for (auto&& p: v) {
            dy = p.first;
            dx = p.second;
            if (grid[y+dy][x+dx] == 1) {
                move = false;
                break;
            }
        }
        if (move) {
            m[make_pair(y+v[1].first, x+v[1].second)].push_back(make_pair(y,x));
            return;
        }
    }
}

void print_grid(vector<vector<int>>& grid) {
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 0)
                cout << ". ";
            else cout << "# ";
        }
        cout << endl;
    }
}

int main() {
    ifstream f("input.txt");
    string line;
    vector<vector<int>> grid;
    int x_size = 1100;
    int y_size = 1100;
    for (int y = 0; y < y_size/2; ++y) {
        vector<int> row(x_size);
        grid.push_back(row);
    }
    while(getline(f,line)) {
        vector<int> row(x_size);
        int x = x_size/2;
        for (auto&& c : line) {
            if (c == '.')
                row[x] = 0;
            else
                row[x] = 1;
            ++x;
        }
        while(x < x_size) {
            row[x] = 0;
            ++x;
        }
        grid.push_back(row);
    }
    for (int y = 0; y < y_size/2; ++y) {
        vector<int> row(x_size);
        grid.push_back(row);
    }
    vector<vector<pair<int,int>>> dirs;
    dirs.push_back( {make_pair(-1,-1),make_pair(-1,0),make_pair(-1,1)} ); // N
    dirs.push_back( {make_pair(1,-1),make_pair(1,0),make_pair(1,1)} ); // S
    dirs.push_back( {make_pair(-1,-1),make_pair(0,-1),make_pair(1,-1)} ); // W
    dirs.push_back( {make_pair(-1,1),make_pair(0,1),make_pair(1,1)} ); // E
    int round = 1;
    while (true) {
        map<pair<int,int>,vector<pair<int,int>>> m;
        bool second_half_called = false;
        for (int y = 0; y < grid.size(); ++y) {
            for (int x = 0; x < grid[y].size(); ++x) {
                if (grid[y][x] == 1 && !first_half(grid,y,x)) {
                    second_half(grid,y,x,m,dirs,second_half_called);
                }
            }
        }
        if (!second_half_called) break;
        for (auto&& kv : m) {
            if (kv.second.size() > 1) continue;
            grid[kv.second[0].first][kv.second[0].second] = 0;
            grid[kv.first.first][kv.first.second] = 1;
        }
        dirs.push_back(dirs[0]);
        dirs.erase(dirs.begin());
        ++round;
    }
    //print_grid(grid); cout << endl;

    cout << round;
}