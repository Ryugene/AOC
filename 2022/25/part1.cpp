#include <bits/stdc++.h>

using namespace std;

typedef long long(ll);

void increment(char& c, ll& res, int& power) {
    switch (c) {
    case '0':
        res += 0; break;
    case '1':
        res += pow(5, power); break;
    case '2':
        res += 2 * pow(5, power); break;
    case '-':
        res -= pow(5, power); break;
    case '=':
        res -= 2 * pow(5, power); break;
    }
}

void SNAFU_to_dec(string& S, ll& res) {
    for (int power = 0; power < S.size(); ++power) {
        char c = S[S.size() - 1 - power];
        increment(c, res, power);
    }
}

void dec_to_SNAFU(vector<ll>& powers, ll n, string& S, int prev_p) {
    int p = 0;
    
    while (n > powers[p] || n < -powers[p])
        ++p;
    ll x = 2 * pow(5, p) - n;
    ll y = -2 * pow(5, p) - n;
    if (S.size() > 0) {
        for (int i = p + 1; i < prev_p; ++i) {
            S.push_back('0');
        }
    }
    if (n == 0) {
        if (prev_p != 0)
            S.push_back('0');
        return;
    }
    if (n > 0 && 2 * pow(5, p) - n <= powers[p - 1]) {
        S.push_back('2');
        n -= 2 * pow(5, p);
    }
    else if (n > 0) {
        S.push_back('1');
        n -= pow(5, p);
    }
    else if (n < 0 && -2 * pow(5, p) - n >= -powers[p - 1]) {
        S.push_back('=');
        n += 2 * pow(5, p);
    }
    else {
        S.push_back('-');
        n += pow(5, p);
    }
    dec_to_SNAFU(powers, n, S, p);
}

int main() {
    ifstream f("input.txt");
    string line;
    ll res = 0;
    while (getline(f, line)) {
        SNAFU_to_dec(line, res);
    }
    vector<ll> powers; powers.push_back(2);
    for (int p = 1; p < 22; ++p) {
        ll x = powers[p - 1] + 2 * pow(5, p);
        powers.push_back(x);
    }
    string S;
    dec_to_SNAFU(powers, res, S, -1);
    cout << S;
}