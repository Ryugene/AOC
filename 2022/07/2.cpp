#include <bits/stdc++.h>
using namespace std;

struct Dir {
    string d_name;
    Dir* parent;
    vector<Dir*> dirs;
    int d_size;
    int total_size; // d_size + d_size of all dirs
    Dir(string name) {
        d_name = name;
        parent = NULL;
        d_size = 0;
        total_size = 0;
    }
};
/*
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
}*/

pair<string,string> mysplit(string line) {
    string c = "";
    string a = "";
    bool space = false;
    for (int i = 0; i < line.size(); ++i) {
        if (line[i] == '$')
            ++i;
        else if (line[i] != ' ' && !space)
            c += line[i];
        else if (line[i] == ' ')
            space = true;
        else
            a += line[i];
    }
    pair<string,string> p(c,a);
    return p;
}

void finddir(Dir*& d, string name) {
    for (int i = 0; i < d->dirs.size(); ++i) {
        if (d->dirs[i]->d_name == name) {
            d = d->dirs[i];
            break;
        }
    }
}

int CalcTotalSize(Dir*& curr) {
    for (int i = 0; i < curr->dirs.size(); ++i) {
        curr->total_size += CalcTotalSize(curr->dirs[i]);
    }
    return curr->total_size;
}

void get_sizes(Dir* curr, vector<int>& dir_sizes) {
    dir_sizes.push_back(curr->total_size);
    for (auto& dir : curr->dirs) {
        get_sizes(dir,dir_sizes);
    }
}

int main() {
    ifstream f("input.txt");
    int solution = 0;
    string line;
    Dir* root = new Dir("/");
    Dir* curr = root;
    while (getline(f,line)) {
        pair <string,string> p = mysplit(line);
        if (p.first[0] >= '0' && p.first[0] <= '9') { //add file_size to curr dirr
            curr->d_size += stoull(p.first);
            curr->total_size = curr->d_size;
        }
        else if (p.first == "dir") { //add dir to curr dir
            Dir* new_dir = new Dir(p.second);
            new_dir->parent = curr;
            curr->dirs.push_back(new_dir);
        }
        else if (p.first == "ls")
            continue;
        else {
            if (p.second == "/")
                curr = root;
            else if (p.second == "..") {
                curr = curr->parent;
            }
            else {
                finddir(curr, p.second);
            }
        }
    }
    CalcTotalSize(root);
    int to_delete = 30000000 - (70000000 - root->total_size); //30 000 000-(70 000 000-49 192 532) = 30 000 000 - 20 807 468 = 9 192 532
    vector<int> dir_sizes;
    get_sizes(root, dir_sizes);
    sort(dir_sizes.begin(), dir_sizes.end());
    cout << *lower_bound(dir_sizes.begin(), dir_sizes.end(), to_delete);
}