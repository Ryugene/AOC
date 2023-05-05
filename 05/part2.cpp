#include <bits/stdc++.h>

using namespace std;

vector<stack<char>> getcrates(ifstream &f) {
    vector<stack<char>> crates;
    string line;
    while (getline(f,line)) {
        stack<char> s;
        for (char &c: line) {
            s.emplace(c);
        }
        crates.push_back(s);
    }
    return crates;
}

vector<vector<int>> getorders(ifstream &f) {
    vector<vector<int>> orders;
    string line;
    while (getline(f,line)) {
        vector<int> order;
        string num;
        int i = 0;
        while (line[i] != ',') {
            num += line[i];
            ++i;
        }
        order.push_back(stoi(num)); //first n 
        ++i;
        num = line[i];
        order.push_back(stoi(num)); //second n
        i += 2;
        num = line[i];
        order.push_back(stoi(num)); //third n
        orders.push_back(order); //insert order
    }
    return orders;
}

void movecrates(vector<stack<char>> &crates, vector<int> &order) {
    vector<char> move;
    for (int i = 0; i < order[0]; ++i) {
        if (!crates[order[1]-1].empty()) {
            char crate = crates[order[1]-1].top();
            crates[order[1]-1].pop();
            move.push_back(crate);
        }
    }
    for (int i = move.size()-1; i >= 0; --i) {
            crates[order[2]-1].emplace(move[i]);
        }
}

int main () {
    ifstream f("crates.txt");
    ifstream g("orders.txt");
    vector<stack<char>> crates = getcrates(f);
    vector<vector<int>> orders = getorders(g);

    for (int i = 0; i < orders.size(); ++i) {
        movecrates(crates, orders[i]);
    }
    for (auto &c : crates) {
        cout << c.top();
    }
}