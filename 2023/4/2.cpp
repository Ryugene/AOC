#include <bits/stdc++.h>

using namespace std;

vector<int> ReadNumbers(string& line, int& ind, int cnt) {
    vector<int> result;
    while (result.size() < cnt) {
        string curr = "";
        while (line[ind] < '0' || line[ind] > '9') {
            ++ind;
        }
        while (line[ind] >= '0' && line[ind] <= '9') {
            curr += line[ind]; ++ind;
        }
        int num = stoi(curr);
        result.push_back(num);
    }
    return result;
}

int main() {
    ifstream f("input.txt");
    string line;
    long long result = 0;
    vector<int> cards(1000);
    int c_ind = 0;
    while(getline(f,line)) {
        cards[c_ind]++;
        int start = line.find(":")+2;
        vector<int> want = ReadNumbers(line,start,10);
        vector<int> have = ReadNumbers(line,start,25);
        /* TEST FOR DUPLICATES:
        set<int> s(have.begin(), have.end());
        if (s.size() != have.size()) {
            cout << "dupl";
        } NO DUPLICATES FOUND */
        long long score = 0;
        for (int i = 0; i < want.size(); ++i) {
            for (int j = 0; j < have.size(); ++j) {
                if (want[i] == have[j])
                        ++score;
            }
        }
        for (int i = 0; i < cards[c_ind]; ++i) {
            for (int j = 0; j < score; ++j) {
                cards[c_ind+j+1]++;
            }
        }
        result += cards[c_ind++];
    }
    cout << result;
}