#include <bits/stdc++.h>

using namespace std;

vector<long long> ReadNumbers(string& line, int ind, int cnt) {
    vector<long long> result;
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
    ifstream f("input2.txt");
    vector<long long> times;
    vector<long long> distances;
    string line;
    while (getline(f, line)) {
        if (line[0] == 'T')
            times = ReadNumbers(line, 10, 1);
        else
            distances = ReadNumbers(line, 10, 1);
    }
    long long wins = 0;
    for (int j = 0; j < times[0]; ++j) {
        if ((times[0]-j)*j > distances[0])
            ++wins; 
    }
    cout << wins;
}