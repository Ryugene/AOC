#include <bits/stdc++.h>

using namespace std;

void direction(char c, int& dy, int& dx) {
    switch(c) {
        case '>':
            dy = 0; dx = 1; break;
        case '<':
            dy = 0; dx = -1; break;
        case '^':
            dy = -1; dx = 0; break;
        case 'v':
            dy = 1; dx = 0; break;
    }
}

void travel(map<pair<int,int>,vector<char>>& new_m, vector<vector<char>>& grid, char c, int y, int x) {
    switch(c) {
        case '>':
            x = 1; break;
        case '<':
            x = grid[y].size()-2; break;
        case '^':
            y = grid.size()-2; break;
        case 'v':
            y = 1; break;
    }
    new_m[make_pair(y,x)].push_back(c);
}

void move_blizzard(vector<vector<char>>& grid, map<pair<int,int>,vector<char>>& m) {
    map<pair<int,int>,vector<char>> new_m;
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (m.find(make_pair(y,x)) != m.end()) {
                for (auto&& c : m[make_pair(y,x)]) {
                    int dy = 0; int dx = 0;
                    direction(c,dy,dx);
                    if (grid[y+dy][x+dx] == '#')
                        travel(new_m,grid,c,y,x);
                    else
                        new_m[make_pair(y+dy,x+dx)].push_back(c);
                }
            }
        }
    }
    m = new_m;
}

void bfs(vector<vector<char>>& grid, map<pair<int,int>,vector<char>>& m, vector<vector<int>>& bfs_grid, pair<int,int> start, pair<int,int> end) {
    queue<pair<int,int>> q;
    q.push(make_pair(start.first,start.second));
    vector<pair<int,int>> dirs;
    dirs.push_back(make_pair(-1,0)); dirs.push_back(make_pair(0,1)); dirs.push_back(make_pair(1,0));
    dirs.push_back(make_pair(0,-1)); dirs.push_back(make_pair(0,0));
    int steps = 1;
    while (true) {
        if (bfs_grid[end.first][end.second] != 1000)
            return;
        move_blizzard(grid,m);
        int sz = q.size();
        map<pair<int,int>,bool> contains;
        for (int j = 0; j < sz; ++j) {
            int y = q.front().first;
            int x = q.front().second;
            q.pop();
            for (auto&& d : dirs) {
                int dy = d.first;
                int dx = d.second;
                if (y+dy < 0 || y+dy >= grid.size() || x+dx < 0 || x+dx >= grid[y].size() || grid[y+dy][x+dx] == '#' || m[make_pair(y+dy,x+dx)].size() > 0)
                    continue;
                if (!contains[make_pair(y+dy,x+dx)]) {
                    q.push(make_pair(y+dy,x+dx));
                    contains[make_pair(y+dy,x+dx)] = true;
                }
                if (bfs_grid[y+dy][x+dx] > steps)
                    bfs_grid[y+dy][x+dx] = steps;
            }
        }
        ++steps;
    }
}

void print_grid(vector<vector<char>>& grid, map<pair<int,int>,vector<char>>& m) {
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (x == grid[y].size()-1 || x == 0 || y == grid.size()-1 || y == 0)
                cout << grid[y][x] << " ";
            else if (m[make_pair(y,x)].size() == 0)
                cout << "." << " ";
            else if (m[make_pair(y,x)].size() == 1)
                cout << m[make_pair(y,x)][0] << " ";
            else
                cout << m[make_pair(y,x)].size() << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void print_bfs(const vector<vector<int>>& grid) {
    int max_width = 0;
    for (auto&& row : grid) {
        for (auto&& element : row) {
            int width = to_string(element).length();
            if (width > max_width) {
                max_width = width;
            }
        }
    }
    for (const auto& row : grid) {
        for (const auto& element : row) {
            cout << setw(max_width) << element << " ";
        }
        cout << endl;
    }
}

void reset_bfs_grid(vector<vector<int>>& bfs_grid, int n) {
    for (int y = 0; y < bfs_grid.size(); ++y) {
        for (int x = 0; x < bfs_grid[0].size(); ++x) {
            bfs_grid[y][x] = n;
        }
    }
}


int main() {
    ifstream f("input.txt");
    string line;
    vector<vector<char>> grid;
    vector<vector<int>> bfs_grid;
    map<pair<int,int>,vector<char>> m;
    int infinity = 1000;
    int y = 0;
    while(getline(f,line)) {
        vector<char> row;
        for (int x = 0; x < line.size(); ++x) {
            row.push_back(line[x]);
            if (line[x] != '.' && line[x] != '#')
                m[make_pair(y,x)].push_back(line[x]);
        }
        vector<int> bfs_row(row.size(),infinity);
        bfs_grid.push_back(bfs_row);
        grid.push_back(row);
        ++y;
    }
    int res = 0;
    bfs(grid, m, bfs_grid, make_pair(0,1), make_pair(grid.size()-1, grid[0].size()-2));
    res += bfs_grid[grid.size()-1][grid[0].size()-2];
    cout << bfs_grid[grid.size()-1][grid[0].size()-2] << endl;
    reset_bfs_grid(bfs_grid,infinity);
    bfs(grid, m, bfs_grid, make_pair(grid.size()-1, grid[0].size()-2), make_pair(0,1));
    res += bfs_grid[0][1];
    cout << bfs_grid[0][1] << endl;
    reset_bfs_grid(bfs_grid,infinity);
    bfs(grid, m, bfs_grid, make_pair(0,1), make_pair(grid.size()-1, grid[0].size()-2));
    res += bfs_grid[grid.size()-1][grid[0].size()-2];
    cout << bfs_grid[grid.size()-1][grid[0].size()-2] << endl;
    cout << res;
}