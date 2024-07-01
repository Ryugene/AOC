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

pair<vector<int>,vector<vector<int>>> update_map(map<vector<int>,vector<vector<int>>>& m, vector<vector<int>>& grid, int h, int r_i, int c_i, int n) {
    vector<int> key; key.push_back(c_i); key.push_back(r_i);
    for (int x = 0; x < 7; ++x) {
        for (int y = h; y >= 0; --y) {
            if (grid[y][x] == 1) {
                key.push_back(h-y);
                break;
            }
        }
    }
    auto&& it = m.find(key);
    vector<int> v; v.push_back(n); v.push_back(h);
    if (it != m.end()) {
        it->second.push_back(v);
        return make_pair(it->first,it->second);
    }
    else {
        vector<vector<int>> val;
        val.push_back(v);
        m.insert(make_pair(key,val));
        return make_pair(key,val);
    }

}

void print_last(pair<vector<int>,vector<vector<int>>>& p) {
    vector<int> k = p.first;
    cout << "[";
    for (int i = 0; i < k.size(); ++i) {
        if (i!= k.size()-1) {
            cout << k[i] << ",";
        }
        else cout << k[i] << "]: ";
    }
    auto&& v = p.second;
    for (int i = 0; i < v.size(); ++i) {
        cout << "[" << v[i][0] << "," << v[i][1] << "], ";
    }
    cout << endl;
}


int main() {
    ifstream f("input.txt");
    string commands;
    getline(f,commands);
    vector<vector<int>> grid(300000);
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
    
    map<vector<int>,vector<vector<int>>> m;
    for (size_t n = 1; n <= 20000; ++n) {
        int r_i = (n-1) % 5;
        start_fall(grid,rocks,h,r_i,commands,c_i);
        pair<vector<int>,vector<vector<int>>> p = update_map(m,grid,h,r_i,c_i,n);
        //print_last(p);
    }

    //cout << h << endl;

    // cycle starts at n = 101
    size_t initial_height = 156;
    size_t cycle_length = 1715;
    // cycle height = 2616
    size_t cycles = (1000000000000 - 101) / cycle_length;
    // cycles = 583090378
    size_t cycles_h = cycles * 2616;
    size_t cycle_h = 1525364428848;
    size_t rem_c = (1000000000000 - 101)% cycle_length;
    // rem_c = 1629
    size_t rem_h = 2483;
    size_t res = initial_height + cycle_h + rem_h;
    cout << res;

}