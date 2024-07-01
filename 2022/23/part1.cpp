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

void second_half(vector<vector<int>>& grid, int y, int x, map<pair<int,int>,vector<pair<int,int>>>& m, vector<vector<pair<int,int>>>& dirs) {
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
    ifstream g("first_line.txt");
    string line;
    vector<vector<int>> grid;
    getline(g,line);
    int x_size = line.size() + 20;
    for (int y = 0; y < 11; ++y) {
        vector<int> row(x_size);
        grid.push_back(row);
    }
    while(getline(f,line)) {
        vector<int> row(x_size);
        int x = 10;
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
    for (int y = 0; y < 11; ++y) {
        vector<int> row(x_size);
        grid.push_back(row);
    }
    vector<vector<pair<int,int>>> dirs;
    dirs.push_back( {make_pair(-1,-1),make_pair(-1,0),make_pair(-1,1)} ); // N
    dirs.push_back( {make_pair(1,-1),make_pair(1,0),make_pair(1,1)} ); // S
    dirs.push_back( {make_pair(-1,-1),make_pair(0,-1),make_pair(1,-1)} ); // W
    dirs.push_back( {make_pair(-1,1),make_pair(0,1),make_pair(1,1)} ); // E
    for (int r = 0; r <= 10; ++r) {
        map<pair<int,int>,vector<pair<int,int>>> m;
        for (int y = 0; y < grid.size(); ++y) {
            for (int x = 0; x < grid[y].size(); ++x) {
                if (grid[y][x] == 1 && !first_half(grid,y,x)) {
                    second_half(grid,y,x,m,dirs);
                }
            }
        }
        for (auto&& kv : m) {
            if (kv.second.size() > 1) continue;
            grid[kv.second[0].first][kv.second[0].second] = 0;
            grid[kv.first.first][kv.first.second] = 1;
        }
        dirs.push_back(dirs[0]);
        dirs.erase(dirs.begin());
    }
    print_grid(grid); cout << endl;
    int res = 0;
    int r_start; int r_end; int c_start; int c_end; // smallest rectangle
    for (int y = 0; y < grid.size(); ++y) {
        bool b = false;
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 1) {
                r_start = y;
                b = true; break;
            }
        }
        if (b) break;
    }
    for (int y = grid.size()-1; y >= 0; --y) {
        bool b = false;
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 1) {
                r_end = y;
                b = true; break;
            }
        }
        if (b) break;
    }
    for (int x = 0; x < grid[0].size(); ++x) {
        bool b = false;
        for (int y = 0; y < grid.size(); ++y) {
            if (grid[y][x] == 1) {
                c_start = x;
                b = true; break;
            }
        }
        if (b) break;
    }
    for (int x = grid[0].size()-1; x >= 0; --x) {
        bool b = false;
        for (int y = 0; y < grid.size(); ++y) {
            if (grid[y][x] == 1) {
                c_end = x;
                b = true; break;
            }
        }
        if (b) break;
    }

    for (int y = r_start; y <= r_end; ++y) {
        for (int x = c_start; x <= c_end; ++x) {
            if (grid[y][x] == 0) ++res;
        }
    }
    cout << res;
}