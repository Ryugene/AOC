#include <bits/stdc++.h>

using namespace std;

void solve(vector<vector<int>>& grid, vector<vector<int>>& dist) {
    queue<pair<int,int>> q;
    vector<pair<int,int>> directions = {make_pair(-1,0), make_pair(0,-1), make_pair(0,1), make_pair(1,0)};
    q.push(make_pair(20,0));
    while (!q.empty()) {
        pair<int,int> curr = q.front(); q.pop();
        int y = curr.first;
        int x = curr.second;
        for (auto&& d : directions) {
            int dy = d.first;
            int dx = d.second;
            if (y+dy >= 0 && y+dy < grid.size() && x+dx >= 0 && x+dx < grid[0].size()) { // out of bounds test
                if (grid[y+dy][x+dx] - grid[y][x] <= 1 && dist[y+dy][x+dx] > dist[y][x]+1) {
                    q.push(make_pair(y+dy,x+dx));
                    dist[y+dy][x+dx] = dist[y][x]+1;
                }
            }
        }
    }
}
void printgrid(vector<vector<int>>& grid) {
    for (int y = 0; y < grid.size(); ++y) {
        cout << "row " << y << ":";
        for (int x = 0; x < grid[y].size(); ++x) {
            cout << grid[y][x] << " ";
        }
        cout << endl;
    }
}

int main() { // S[20,0] , E[20,148]
    ifstream f("input.txt");
    string line;
    vector<vector<int>> grid;
    vector<vector<int>> dist;
    while (getline(f,line)) { 
            vector<int> row;
            vector<int> dist_row;
            for (auto&& c : line) {
                if (c == 'E') 
                    row.push_back(122);
                
                else if (c == 'S') 
                    row.push_back(97);
                else
                    row.push_back((int)c);
            }
            grid.push_back(row);
            dist_row.resize(row.size(),10000);
            dist.push_back(dist_row);
    }
    dist[20][0] = 0; // Start
    solve(grid,dist);
    //printgrid(dist);
    cout << dist[20][148];
}