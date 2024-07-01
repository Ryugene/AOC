#include <bits/stdc++.h>

using namespace std;



int calc_m_distance(pair<int,int> s, pair<int,int> b) {
    return (abs(s.first - b.first) + abs(s.second - b.second));
}

bool is_within_radius(vector<pair<pair<int,int>,int>> s_radiuses, pair<int,int> sensor, pair<int,int> p) {
    if (p.first < 0 || p.first > 4000000 || p.second < 0 || p.second > 4000000)
        return true;
    for (int i = 0; i < s_radiuses.size(); ++i) {
        if (s_radiuses[i].first != sensor) {
            int dist_p = calc_m_distance(s_radiuses[i].first,p);
            if (s_radiuses[i].second >= dist_p)
                return true;
        }
    }
    return false;
}

void findbeacon(vector<pair<pair<int,int>,int>> s_radiuses, pair<long long, long long>& res) {
    for (auto&& s_p: s_radiuses) {
        int new_r = s_p.second+1;
        int s_x = s_p.first.first;
        int s_y = s_p.first.second;
        for (int i = 0; i <= new_r; ++i) {
            pair<int,int> p1(s_x+i,s_y-new_r+i);
            pair<int,int> p2(s_x-i,s_y-new_r+i);
            if (!is_within_radius(s_radiuses,s_p.first,p1)) {
                res = p1; return;
            }
            if (!is_within_radius(s_radiuses,s_p.first,p2)) {
                res = p2; return;
            }
            p1 = make_pair(s_x+i,s_y+new_r-i);
            p2 = make_pair(s_x-i,s_y+new_r-i);
            if (!is_within_radius(s_radiuses,s_p.first,p1)) {
                res = p1; return;
            }
            if (!is_within_radius(s_radiuses,s_p.first,p2)) {
                res = p2; return;
            }
        }
    }
}
int main() { // x [-626 874,3 953 907] (diff 4 580 781) 2 290 390 y [-101788,3976937] (diff 4 078 725)
    ifstream f("input.txt");
    string line;
    vector<pair<pair<int,int>,int>> s_radiuses;
    pair<long long, long long> res(-1,-1);
    while(getline(f,line)) {
        size_t i = 0;
        size_t ind = 0;
        int s_x = stoi(line,&ind);
        i += ind;
        int s_y = stoi(line.substr(i),&ind);
        i += ind;
        int b_x = stoi(line.substr(i),&ind);
        i += ind;
        int b_y = stoi(line.substr(i),&ind);
        int r = calc_m_distance(make_pair(s_x,s_y),make_pair(b_x,b_y));
        s_radiuses.push_back(make_pair(make_pair(s_x,s_y),r));
    }
    findbeacon(s_radiuses,res);
    long long result = res.first*4000000 + res.second;
    cout << result;
}