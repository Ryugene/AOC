#include <bits/stdc++.h>

using namespace std;

int fill_water(vector<vector<vector<int>>>& matrix, vector<vector<vector<int>>>& bfs, vector<tuple<int,int,int>>& v) {
    int res = 0;
    queue<tuple<int,int,int>> q;
    tuple<int,int,int> curr(0,0,25);
    q.push(curr);
    while (!q.empty()) {
        curr = q.front(); q.pop();
        for (int i = 0; i < v.size(); ++i) {
            int n_x = get<0>(curr) + get<0>(v[i]);
            int n_y = get<1>(curr) + get<1>(v[i]);
            int n_z = get<2>(curr) + get<2>(v[i]);
            if (n_x < 0 || n_y < 0 || n_z < 0 || n_x > 25 || n_y > 25 || n_z > 25) {
                continue;
            }
            if (matrix[n_x][n_y][n_z] == 1) {
                ++res;
                continue;
            }
            tuple<int,int,int> n_curr(n_x,n_y,n_z);
            if (bfs[n_x][n_y][n_z] == 0) {
                q.push(n_curr);
                bfs[n_x][n_y][n_z] = 1;
            }
        }
    }
    return res;
}

int main() { // 20x21x21 maxes
    ifstream f("input.txt");
    string line;
    int n = 27;
    vector<vector<vector<int>>> matrix;
    vector<vector<vector<int>>> bfs;
    for (int z = 0; z < n; ++z) {
        vector<vector<int>> surface;
        for (int y = 0; y < n; ++y) {
            vector<int> row(n);
            surface.push_back(row);
        }
        matrix.push_back(surface);
        bfs.push_back(surface);
    }
    
    while (getline(f,line)) {
        size_t i = 0;
        size_t ind = i;
        int x = stoi(line.substr(0),&ind); ++ind; i += ind;
        int y = stoi(line.substr(i),&ind); ++ind; i+= ind;
        int z = stoi(line.substr(i));
        matrix[x][y][z] = 1;
    }
    vector<tuple<int,int,int>> v;
    tuple<int,int,int> t1(0,1,0); tuple<int,int,int> t2(1,0,0); tuple<int,int,int> t3(0,-1,0);
    tuple<int,int,int> t4(-1,0,0); tuple<int,int,int> t5(0,0,1); tuple<int,int,int> t6(0,0,-1);
    v.push_back(t1); v.push_back(t2); v.push_back(t3); v.push_back(t4); v.push_back(t5); v.push_back(t6);
    
    int res = fill_water(matrix,bfs,v);
    cout << res +2 ; // because there are exactly 2 cubes at index 0
}