#include <bits/stdc++.h>

using namespace std;

void printgrid(vector<vector<int>>& grid, int& h) {
    for (int y = h+5; y >= 0; --y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 1) cout << '#';
            else cout << '.';
        }
        cout << endl;
    }
    cout << endl;
}

bool can_fall(vector<vector<int>>& grid, vector<pair<int,int>>& curr, int& h) {
    for (auto&& r : curr) {
        int y = r.first+h;
        int x = r.second;
        if (y-1 == 0 || grid[y-1][x] == 1)
            return false;
    }
    return true;
}

bool can_move(vector<vector<int>>& grid, vector<pair<int,int>>& curr, int& h, char c) {
    for (auto&& r : curr) {
        int y = h+r.first;
        int x = r.second;
        if (c == '<') {
            if (x-1 < 0 || grid[y][x-1] == 1) {
                return false;
            }
        }
        else {
            if (x+1 >= 7 || grid[y][x+1] == 1) {
                return false;
            }
        }
    }
    return true;
}

void move(vector<pair<int,int>>& curr, char c) {
    for (auto&& r : curr) {
        if (c == '<') {
            r.second -= 1;
        }
        else {
            r.second += 1;
        }
    }
    
}

void fall(vector<pair<int,int>>& curr) {
    for (auto&& r : curr) {
        r.first -= 1;
    }

}

void start_fall(vector<vector<int>>& grid, vector<vector<pair<int,int>>>& rocks, int& h, int r_i, string& commands, int& c_i) {
    vector<pair<int,int>> curr = rocks[r_i];
    while (true) {
        if (can_move(grid,curr,h,commands[c_i])) {
            move(curr,commands[c_i]);
        }
        c_i = (c_i+1) % commands.size();
        if (can_fall(grid,curr,h))
            fall(curr);
        else break;
    }
    int mxh = h;
    for (auto&& r : curr) {
        grid[r.first+h][r.second] = 1;
        mxh = max(r.first+h,h);
    }
    h = mxh;
}



int main() {
    ifstream f("input.txt");
    string commands;
    getline(f,commands);
    vector<vector<int>> grid(10000);
    for (auto&& r : grid) {
        r.resize(7);
    }
    int h = 0;
    int c_i = 0;
    vector<vector<pair<int,int>>> rocks;
    vector<pair<int,int>> r1; vector<pair<int,int>> r2; 
    vector<pair<int,int>> r3; vector<pair<int,int>> r4;
    vector<pair<int,int>> r5;
    pair<int,int> p11(4,2); pair<int,int> p12(4,3); pair<int,int> p13(4,4); pair<int,int> p14(4,5);
    r1.push_back(p11); r1.push_back(p12); r1.push_back(p13); r1.push_back(p14);
    pair<int,int> p21(4,3); pair<int,int> p22(5,2); pair<int,int> p23(5,3); pair<int,int> p24(5,4); pair<int,int> p25(6,3);
    r2.push_back(p21); r2.push_back(p22); r2.push_back(p23); r2.push_back(p24); r2.push_back(p25);
    pair<int,int> p31(4,2); pair<int,int> p32(4,3); pair<int,int> p33(4,4); pair<int,int> p34(5,4); pair<int,int> p35(6,4);
    r3.push_back(p31); r3.push_back(p32); r3.push_back(p33); r3.push_back(p34); r3.push_back(p35);
    pair<int,int> p41(4,2); pair<int,int> p42(5,2); pair<int,int> p43(6,2); pair<int,int> p44(7,2);
    r4.push_back(p41); r4.push_back(p42); r4.push_back(p43); r4.push_back(p44);
    pair<int,int> p51(4,2); pair<int,int> p52(4,3); pair<int,int> p53(5,2); pair<int,int> p54(5,3);
    r5.push_back(p51); r5.push_back(p52); r5.push_back(p53); r5.push_back(p54);
    rocks.push_back(r1); rocks.push_back(r2); rocks.push_back(r3); rocks.push_back(r4); rocks.push_back(r5);
    
    for (int n = 1; n <= 2022; ++n) {
        int r_i = (n-1) % 5;
        start_fall(grid,rocks,h,r_i,commands,c_i);
    }
    cout << h;
}