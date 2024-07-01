#include <bits/stdc++.h>

using namespace std;

bool isdup(string s) {
    vector<int> v(26);
    for (int i = 0; i < s.size(); ++i) {
        v[s[i]-97] += 1;
        if(v[s[i]-97] > 1)
            return true;
    }
    return false;
}


int main() {
    ifstream f("input.txt");
    string in;
    while(getline(f,in)) {} //just one row
    string v;
    for (int i = 0; i < 14; ++i) {
        v += in[i];
    }
    int ans;
    for (int i = 14; i < in.size(); ++i) {
        v.erase(v.begin());
        v += in[i];
        if(!isdup(v)) {
            ans = i+1;
            break;
        }
    }
    cout << ans;
}