#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll solve(map<string,string>& m, string name) {
    string p = m[name];
    if (p[0] >= '0' && p[0] <= '9')
        return stoll(p);
    string first = p.substr(0,4);
    char op = p[5];
    string second = p.substr(7);
    ll n1 = solve(m,first);
    ll n2 = solve(m,second);
    ll res = 0;
    if (op == '+') {
        m[name] = to_string(n1+n2);
        res = n1+n2;
    }
    else if (op == '-') {
        m[name] = to_string(n1-n2);
        res = n1-n2;
    }
    else if (op == '*') {
        m[name] = to_string(n1*n2);
        res = n1*n2;
    }
    else {
        m[name] = to_string(n1/n2);
        res = n1/n2;
    }
    if (name == "root")
        cout << n1 << " " << n2 << endl;
    return res;
}

int main() {
    ifstream f("input.txt");
    string line;
    map<string,string> m;
    while (getline(f,line)) {
        string key = line.substr(0,4);
        string value = line.substr(6);
        m.insert(make_pair(key,value));
    }
    ll res = solve(m,"root");
    cout << res;
}