#include <bits/stdc++.h>

using namespace std;

vector<int> ReadNumbers(string& line, int ind, int cnt) {
    vector<int> result;
    while (result.size() < cnt && ind < line.size()) {
        string curr = "";
        while (line[ind] < '0' || line[ind] > '9') {
            ++ind;
        }
        while (line[ind] >= '0' && line[ind] <= '9') {
            curr += line[ind]; ++ind;
        }
        result.push_back(stoi(curr));
    }
    return result;
}

int main() {
    ifstream f("input1.txt");
    vector<int> times;
    vector<int> distances;
    string line;
    while (getline(f, line)) {
        if (line[0] == 'T')
            times = ReadNumbers(line, 10, 4);
        else
            distances = ReadNumbers(line, 10, 4);
    }
    long long result = 1;
    for (int i = 0; i < times.size(); ++i) {
        long long wins = 0;
        for (int j = 0; j < times[i]; ++j) {
            if ((times[i]-j)*j > distances[i])
                ++wins; 
        }
        result *= wins;
    }
    cout << result;
}