#include <bits/stdc++.h>

using namespace std;

string extract_bracket(string& s) {
    int i = 0;
    string element;
    int open_b = 0;
    int closed_b = 0;
    while (i < s.size()) {
        if (s[i] == '[')
            ++open_b;
        else if (s[i] == ']')
            ++closed_b;

        element += s[i];

        if (open_b == closed_b)  {
            element.erase(0,1);
            element.erase(element.size()-1,1);
            return element;
        }
        ++i;
    }
    return element;
}



bool evaluate(string& l, string& r) {
    if (l.size() == 0)
        return true;
    if (r.size() == 0)
        return false;
    if (l[0] == '[' && r[0] == '[') {
        string new_l = extract_bracket(l);
        string new_r = extract_bracket(r);
        if (new_l == new_r) {
            l.erase(0,new_l.size()+3);
            r.erase(0,new_r.size()+3);
            return evaluate(l,r);
        }
        return evaluate(new_l,new_r);
    }
    else if (l[0] == '[') {
        string new_l = extract_bracket(l);
        if (find(new_l.begin(),new_l.end(),',') != new_l.end() || l[0] == '[') {
            return evaluate(new_l,r);
        }
        if (stoi(new_l) < stoi(r))
            return true;
        else if (stoi(new_l) == stoi(r)) {
            l.erase(0,new_l.size()+3);
            r.erase(0,new_l.size()+1);
            return evaluate(l,r);
        }
        else
            return false;
    }
    else if (r[0] == '[') {
        string new_r = extract_bracket(r);
        if (find(new_r.begin(),new_r.end(),',') != new_r.end() || r[0] == '[') {
            return evaluate(l,new_r);
        }
        if (stoi(l) < stoi(new_r))
            return true;
        else if (stoi(l) == stoi(new_r)) {
            l.erase(0,new_r.size()+1);
            r.erase(0,new_r.size()+3);
            return evaluate(l,r);
        }
        else
            return false;
    }
    else {
        if (stoi(l) == stoi(r)) {
            l.erase(0,int(log10(stoi(l)) + 2));
            r.erase(0,int(log10(stoi(r)) + 2));
            return evaluate(l,r);
        }
        else if (stoi(l) < stoi(r))
            return true;
        else return false;
    }
    return true;
}

/*vector<string> extract(string s) {
    int i = 0;
    vector<string> v_s;
    string element;
    int open_b = 0;
    int closed_b = 0;
    while (i < s.size()) {
        if (s[i] == '[')
            ++open_b;
        else if (s[i] == ']')
            ++closed_b;

        element += s[i];

        if (open_b == closed_b && open_b != 0)  {
            v_s.push_back(element);
            element.clear();
            ++i;
            open_b = 0;
            closed_b = 0;
        }
        ++i;
    }
    return v_s;
}*/


int main() {
    ifstream f("input.txt");
    string line;
    string l;
    string r;
    int counter = 0;
    int res = 1;
    vector<string> items;
    items.push_back("[[2]]");
    items.push_back("[[6]]");
    while (getline(f,line)) {
        if (line.size() == 0) {
            continue;
        }
        items.push_back(line);
    }
    for (int i = 0; i < items.size()-1; ++i) {
        for (int j = 0; j < items.size()-i-1; ++j) {
            string tmp = items[j+1];
            if (!evaluate(items[j],items[j+1])) { // l > r
                items[j+1] = items[j];
                items[j] = tmp;
            }
        }
    }
    for (int i = 0; i < items.size(); ++i) {
        if (items[i] == "[[2]]" || items[i] == "[[6]]")
            res *= (i+1);
    }
    cout << res;
}