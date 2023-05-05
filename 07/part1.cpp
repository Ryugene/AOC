#include <bits/stdc++.h>
using namespace std;

struct Dir {
    string d_name;
    Dir* parent;
    vector<Dir*> dirs;
    unsigned long long d_size;
    unsigned long long total_size; // d_size + d_size of all dirs
    Dir(string name) {
        d_name = name;
        parent = NULL;
        d_size = 0;
    }
    
    

};

unsigned long long CalcTotalSize(Dir*& curr) {
    for (int i = 0; i < curr->dirs.size(); ++i) {
        curr->total_size += CalcTotalSize(curr->dirs[i]);
    }
    if (curr->total_size <= 100000)
        cout << curr->d_name << ":" << curr->total_size << endl;
    return curr->total_size;
}

void Solve(Dir*& dir,unsigned long long& solution) {
    for (int i = 0; i < dir->dirs.size(); ++i) {
        Solve(dir->dirs[i], solution);
    }
    if (dir->total_size <= (unsigned long long)100000)
        solution += dir->total_size;
}


void finddir(Dir*& d, string name) {
    for (int i = 0; i < d->dirs.size(); ++i) {
        if (d->dirs[i]->d_name == name) {
            d = d->dirs[i];
            break;
        }
    }
}


void printdir(Dir* d, int ln) {

    cout << ln << ":" << d->d_name << ":" << d->total_size << ":";
    if (d->parent != NULL) {
        cout << d->parent->d_name;
    }
    cout << endl;
    for (int i = 0; i < d->dirs.size(); ++i) {
        cout << d->dirs[i]->d_name << ", ";
    }
    cout << endl << endl;
}

pair<string,string> mysplit(string line) {
    string c;
    string a;
    bool space = false;
    for (auto& ch: line) {
        if (ch != ' ' && !space)
            c += ch;
        else if (ch == ' ')
            space = true;
        else
            a += ch;
    }
    pair<string,string> p(c,a);
    return p;
}

int main() {
    ifstream f("input.txt");
    unsigned long long solution = 0;
    int ln = 1;
    string line;
    Dir* root = new Dir("/");
    Dir* curr = root;
    while (getline(f,line)) {
        pair <string,string> p = mysplit(line);
        if (p.first[0] >= '0' && p.first[0] <= '9') { //add file_size to curr dirr
            curr->d_size += stoull(p.first);
            curr->total_size = curr->d_size;
            //printdir(curr_dir,ln);
        }
        else if (p.first == "dir") { //add dir to curr dir
            Dir* new_dir = new Dir(p.second);
            new_dir->parent = curr;
            curr->dirs.push_back(new_dir);
            //printdir(curr_dir,ln);
        }
        else {
            if (p.second == "/")
                curr = root;
            else if (p.second == "..") {
                curr = curr->parent;
            }
            else {
                finddir(curr, p.second);
            }
            //printdir(curr_dir,ln);
        }
        ++ln;
    }
    CalcTotalSize(root);
    Solve(root, solution);
    cout << solution;
}