#include <bits/stdc++.h>

using namespace std;

class node {
public:
    node(int v, node* nxt, node* prv, int mult) {
        val = v;
        next = nxt;
        prev = prv;
        multiply = mult;
    }
    int val;
    int multiply;
    node* next;
    node* prev;
};

node* find_node(node* start, int target) {
    while (start->val != target) {
        start = start->next;
    }
    return start;
}

node* move_right(node* start, node*& curr, int n) {
    node* prev = curr->prev;
    node* next = curr->next;
    node* nn = curr->next->next;
    if (n != 0) {
        if (curr->val == start->val)
            start = start->next;
        prev->next = next;
        next->prev = prev;
        nn->prev = curr;
        next->next = curr;
        curr->next = nn;
        curr->prev = next;
        move_right(start, curr, n - 1);
    }
    return start;
}

node* move_left(node* start, node*& curr, int n) {
    node* pp = curr->prev->prev;
    node* prev = curr->prev;
    node* next = curr->next;
    if (n != 0) {
        if (start->val == curr->val)
            start = start->next;
        next->prev = prev;
        prev->next = next;
        prev->prev = curr;
        pp->next = curr;
        curr->next = prev;
        curr->prev = pp;
        move_left(start, curr, n + 1);
    }
    return start;
}

node* getval(node* start, int i) {
    while (i != 0) {
        start = start->next;
        --i;
    }
    return start;
}

void print_list(node* start, int sz) {
    for (int i = 0; i < sz; ++i) {
        cout << start->val << endl;
        start = start->next;
    }
}
int main() {
    ifstream f("input.txt");
    string line;
    vector<pair<int,int>> sequence; // numbers are not unique
    int i = 1;
    while (getline(f, line)) {
        int n = stoi(line);
        
        if (n > 0) {
            sequence.push_back(make_pair(n+(4999*i),i));
        }
        else if (n < 0) {
            sequence.push_back(make_pair(n-(4999*i),i));
        }
        else
            sequence.push_back(make_pair(0,0));
        ++i;
    }
    node* start = new node(sequence[0].first, NULL, NULL,1);
    node* prev = start;
    int sz = sequence.size();
    for (int i = 1; i < sz; ++i) {
        node* curr = new node(sequence[i].first, NULL, prev,sequence[i].second);
        prev->next = curr;
        prev = curr;
    }
    prev->next = start;
    start->prev = prev;
    for (auto&& n : sequence) {
        int new_n = n.first;
        if (new_n > 0) {
            new_n -= 4999*n.second;
        }
        if (new_n < 0) {
            new_n += 4999*n.second;
        }
        node* curr = find_node(start, n.first);
        if (new_n > 0)
            start = move_right(start, curr, new_n);
        else if (new_n < 0)
            start = move_left(start, curr, new_n);
    }
    //print_list(start,sz); cout <<endl;
    node* zero = find_node(start, 0);
    node* n1 = getval(zero, 1000);
    node* n2 = getval(zero, 2000);
    node* n3 = getval(zero, 3000);
    int v1; int v2; int v3;
    if (n1->val > 0)
        v1 = n1->val - (n1->multiply*4999);
    else if (n1->val < 0)
        v1 = n1->val +(n1->multiply*4999);
    if (n2->val > 0)
        v2 = n2->val - (n2->multiply*4999);
    else if (n2->val < 0)
        v2 = n2->val + (n2->multiply*4999);
    if (n3->val > 0)
        v3 = n3->val - (n3->multiply*4999);
    else if (n3->val < 0)
        v3 = n3->val +(n3->multiply*4999);
    cout << v1 +v2 + v3;
}