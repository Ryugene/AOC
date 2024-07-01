#include <bits/stdc++.h>

using namespace std;

int count_empty(vector<vector<vector<int>>>& matrix, int x, int y, int z) {
    vector<tuple<int,int,int>> v;
    int empty = 0;
    tuple<int,int,int> t1(0,1,0); tuple<int,int,int> t2(1,0,0); tuple<int,int,int> t3(0,-1,0);
    tuple<int,int,int> t4(-1,0,0); tuple<int,int,int> t5(0,0,1); tuple<int,int,int> t6(0,0,-1);
    v.push_back(t1); v.push_back(t2); v.push_back(t3); v.push_back(t4); v.push_back(t5); v.push_back(t6);
    for (int i = 0; i < v.size(); ++i) {
        int n_x = x + get<0>(v[i]);
        int n_y = y + get<1>(v[i]);
        int n_z = z + get<2>(v[i]);
        if (n_x < 0 || n_y < 0 || n_z < 0) {
            ++empty;
            continue;
        }
        if (matrix[n_x][n_y][n_z] == 0)
            ++empty;
    }
    return empty;
}


int main() { // 20x21x21 maxes
    ifstream f("input.txt");
    string line;
    int n = 23;
    vector<vector<vector<int>>> matrix;
    for (int z = 0; z < n; ++z) {
        vector<vector<int>> surface;
        for (int y = 0; y < n; ++y) {
            vector<int> row(n);
            surface.push_back(row);
        }
        matrix.push_back(surface);
    }
    while (getline(f,line)) {
        size_t i = 0;
        size_t ind = i;
        int x = stoi(line.substr(0),&ind); ++ind; i += ind;
        int y = stoi(line.substr(i),&ind); ++ind; i+= ind;
        int z = stoi(line.substr(i));
        matrix[x][y][z] = 1;
    }
    int res = 0;
    for (int z = 0; z < n; ++z) {
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                if (matrix[x][y][z] == 1) {
                    res += count_empty(matrix,x,y,z);
                }
            }
        }
    }
    cout << res;
}