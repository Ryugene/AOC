#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

int main() {
    ifstream f("input.txt");
    string line;
    ll res = 0;
    while (getline(f,line)) {
        int start = 0;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == ':') {
                start = i + 2; break;
            }   
        }
        ll r = 0;
        ll g = 0;
        ll b = 0;
        bool cant = false;
        while (start < line.size() && !cant) {
            ll x = 0;
            while (line[start] >= '0' && line[start] <= '9') {
                x *= 10;
                x += (line[start] - '0');
                ++start;
            }
            ++start;
            if (line[start] == 'r') {
                r = max(r,x);
                start += 3;
            }
            else if (line[start] == 'g') {
                g = max(g,x);
                start += 5;
            }
            else {
                b = max(b,x);
                start += 4;
            }
            start += 2;
        }
        if (!cant)
            res += (r*g*b);
    }
    cout << res;
}