#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll solve(map<string, string>& m, string name) {
    string p = m[name];
    if (p[0] >= '0' && p[0] <= '9')
        return stoll(p);
    string first = p.substr(0, 4);
    char op = p[5];
    string second = p.substr(7);
    ll n1 = solve(m, first);
    ll n2 = solve(m, second);
    ll res = 0;
    if (op == '+') {
        m[name] = to_string(n1 + n2);
        res = n1 + n2;
    }
    else if (op == '-') {
        m[name] = to_string(n1 - n2);
        res = n1 - n2;
    }
    else if (op == '*') {
        m[name] = to_string(n1 * n2);
        res = n1 * n2;
    }
    else {
        m[name] = to_string(n1 / n2);
        res = n1 / n2;
    }
    return res;
}

void get_equation(map<string, string>& m, string name, string& eq) { // root = jhpn + jmsg
    string p = m[name];
    //if (p[0] < '0' && p[0] > '9') {
    p.insert(0, "(");
    p.insert(p.size(), ")");
    //}
    eq.replace(eq.find(name), 4, p);
    if (p[1] >= '0' && p[1] <= '9')
        return;
    string first = p.substr(1, 4);
    string second = p.substr(8, 4);
    if (first != "humn")
        get_equation(m, first, eq);
    if (second != "humn")
        get_equation(m, second, eq);
}

void solve_eq(string& eq, int start, int end) {
    int l = end - (start + 1);
    string s = eq.substr(start + 1, l);

}

string simplify(string& eq, int start, int end) {
    int left = 1, right = 0;
    string s = "";
    int i = start + 1;
    while (left != right) {
        start += eq[i];
        if (eq[i] == '(') ++left;
        else if (eq[i] == ')') ++right;
        ++i;
    }
        --i;
    return s;
}

int main() {
    ifstream f("input.txt");
    string line;
    map<string, string> m;
    while (getline(f, line)) {
        string key = line.substr(0, 4);
        string value = line.substr(6);
        m.insert(make_pair(key, value));
    }
    //ll res = solve(m,"root");
    //cout <<res;
    /*string s = "pppw * xdxd";
    string l = "hhfd + dfsw";
    l.insert(0,"(");
    l.insert(l.size(),")");
    s.replace(s.find("pppw"),4,l);
    cout << s;*/
    string lhs = "jhpn";
    string rhs = "jmsg";
    get_equation(m, lhs, lhs);
    get_equation(m, rhs, rhs);
    fstream file("output.txt");
    file << lhs << "=" << rhs;
    file.close();
    string test = "((1) + (2)) + (1)";
    simplify(test,0,test.size());
    //cout << lhs << "=" << rhs;
}