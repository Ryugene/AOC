#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<ll> ReadNumbers(string& line, int ind, int cnt) {
    vector<ll> result;
    while (result.size() < cnt && ind < line.size()) {
        string curr = "";
        while (line[ind] < '0' || line[ind] > '9') {
            ++ind;
        }
        while (line[ind] >= '0' && line[ind] <= '9') {
            curr += line[ind]; ++ind;
        }
        result.push_back(stoll(curr));
    }
    return result;
}

int main() {
    ifstream f("input.txt");
    string line;
    vector<ll> seeds;
    vector<vector<vector<ll>>> maps(7);
    int li = 0; // line index - used for start
    int mi = -1; // map index
    while (getline(f,line)) {
        if (!li)
            seeds = ReadNumbers(line,7,100);
        else if (!line.size())
            continue;
        else if (line[0] < '0' || line[0] > '9') {
            ++mi;
            continue;
        }
        else {
            vector<ll> ranges = ReadNumbers(line, 0, 3);
            maps[mi].push_back(ranges);
        }
        ++li;
    }
    ll result = LLONG_MAX;
    for (auto& seed : seeds) {
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < maps[i].size(); ++j) {
                if (seed >= maps[i][j][1] && seed <= maps[i][j][1] + maps[i][j][2]-1) {
                    seed = maps[i][j][0] + (seed - maps[i][j][1]);
                    break;
                }
            }
        }
        result = min(result, seed);
    }
    cout << result;
}