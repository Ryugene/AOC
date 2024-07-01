#include <bits/stdc++.h>

using namespace std;

void fillrow(vector<int>& row, int s_x, int s_y, int b_x, int b_y, int& res) {
    int beacon_dist = abs(s_x - b_x) + abs(s_y - b_y);
    int y_dist = abs(s_y - 2700000);
    int n = beacon_dist - y_dist;
    for (int i = 0; i <= n; ++i) {
        if (row[s_x+i] != 1)
            ++res;
        row[s_x+i] = 1;
        if (row[s_x-i] != 1)
            ++res;
        row[s_x-i] = 1;
    }
}

int main() { // x [-626 874,3 953 907] (diff 4 580 781) 2 290 390 y [-101788,3976937] (diff 4 078 725)
    ifstream f("input.txt");
    string line;
    vector<int> row(10000000); // 0 at 700 000
    int res = -1; // one beacon at 2 000 000
    while(getline(f,line)) {
        size_t i = 0;
        size_t ind = 0;
        int s_x = stoi(line,&ind) + 700000;
        i += ind;
        int s_y = stoi(line.substr(i),&ind) + 700000;
        i += ind;
        int b_x = stoi(line.substr(i),&ind) + 700000;
        i += ind;
        int b_y = stoi(line.substr(i),&ind) + 700000;
        fillrow(row,s_x,s_y,b_x,b_y,res);
    }
    cout << res;
}