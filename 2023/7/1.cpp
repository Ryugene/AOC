#include <bits/stdc++.h>

using namespace std;

void check_five(pair<string,int>& cards, vector<pair<string,int>>& five) {
    string c = cards.first;
    set<char> s(c.begin(), c.end());
    if (s.size() == 1)
        five.push_back(cards);
}

void check_four_fh(pair<string,int>& cards, vector<pair<string,int>>& four, vector<pair<string,int>>& fh) {
    string c = cards.first;
    set<char> s(c.begin(), c.end());
    if (s.size() == 2) {
        int frst = 0;
        int scnd = 0;
        for (auto& card: c) {
            if (card == c[0])
                ++frst;
            else
                ++scnd;
        }
        if (frst == 4 || scnd == 4)
            four.push_back(cards);
        else
            fh.push_back(cards);
    }  
}

void check_three_two(pair<string,int>& cards, vector<pair<string,int>>& three, vector<pair<string,int>>& two) {
    string c = cards.first;
    set<char> s(c.begin(), c.end());
    if (s.size() == 3) {
        char c_frst = *s.begin();
        char c_scnd = *next(s.begin(),1);
        int frst = 0;
        int scnd = 0;
        int thrd = 0;
        for (char& card: c) {
            if (card == c_frst)
                ++frst;
            else if (card == c_scnd)
                ++scnd;
            else
                ++thrd;
        }
        if ((frst == 2 && scnd == 2) || (frst == 2 && thrd == 2) || (scnd == 2 && thrd == 2))
            two.push_back(cards);
        else
            three.push_back(cards);
    } 
}

void check_pair_high(pair<string,int>& cards, vector<pair<string,int>>& one, vector<pair<string,int>>& high) {
    string c = cards.first;
    set<char> s(c.begin(), c.end());
    if (s.size() == 4)
        one.push_back(cards);
    else if (s.size() == 5)
        high.push_back(cards);
}

void assign(pair<string, int>& cards, vector<pair<string,int>>& five, vector<pair<string,int>>& four, vector<pair<string,int>>& fh, vector<pair<string,int>>& three ,vector<pair<string,int>>& two, vector<pair<string,int>>& one, vector<pair<string,int>>& high) {
    check_five(cards, five);
    check_four_fh(cards, four, fh);
    check_three_two(cards,three, two);
    check_pair_high(cards, one, high);
}

int assign_value(char& c) {
    vector<char> char_cards = {'T', 'J', 'Q', 'K', 'A'};
    for (int i = 0; i < 5; ++i) {
        if (c == char_cards[i])
            return i+10;
    }
    return 0;
}

bool compare(string& a, string& b) {
    for (int i = 0; i < 5; ++i) {
        int a_val = assign_value(a[i]);
        int b_val = assign_value(b[i]);
    }
}

void card_sort(pair<string, int>& cards, vector<pair<string,int>>& to_sort, vector<pair<string,int>>& sorted) {
    
}

void print_vec(vector<pair<string,int>>& v) {
    for (auto& vi : v) {
        cout << vi.first << endl;
    }
    cout << endl;
}

int main() {
    ifstream f("input.txt");
    vector<pair<string,int>> five;
    vector<pair<string,int>> four;
    vector<pair<string,int>> fh;
    vector<pair<string,int>> three;
    vector<pair<string,int>> two;
    vector<pair<string,int>> one;
    vector<pair<string,int>> high;
    string line;
    while (getline(f, line)) {
        string c = line.substr(0,5);
        int bid = stoi(line.substr(6));
        pair<string, int> cards = make_pair(c,bid);
        assign(cards, five, four, fh, three, two, one, high);
    }

}