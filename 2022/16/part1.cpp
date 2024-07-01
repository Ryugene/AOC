#include <bits/stdc++.h>

using namespace std;

class vertex {
public:
    vertex(string n, int v, int i) {
        name = n;
        val = v;
        index = i;
    }
    string name;
    int val;
    int index;
    vector<vertex*> neighbors;

    bool operator==(vertex* v) {
        if (name == v->name)
            return true;
    }
};



void shortestpath(vertex* s, vertex* f, vector<vector<int>>& distances) {
    queue<pair<vertex*,int>> q;
    vector<int> d(54,100000);
    d[s->index] = 0;
    q.emplace(make_pair(s,0));
    while (!q.empty()) {
        vertex* curr = q.front().first;
        int dist = q.front().second;
        q.pop();
        for (auto&& v : curr->neighbors) {
            if (d[v->index] > dist+1) {
                q.emplace(v,dist+1);
                d[v->index] = dist+1;
            }
        }
    }
    distances[s->index][f->index] = d[f->index];
}


int solve(vertex* v, int time, vector<vertex*> active, int res,const vector<vector<int>>& distances, vector<vertex*> vertices) {
    if(time <= 0) {
        return res;
    }
    if (find(active.begin(),active.end(),v) == active.end() && time >= 1) {
        active.push_back(v);
        return solve(v,time-1,active,res + (v->val*(time-1)),distances,vertices);
    }
    int mx = 0;
    for (auto&& curr : vertices) {
        if (v != curr && find(active.begin(),active.end(),curr) == active.end()) {
            mx = max(mx,solve(curr,time-distances[v->index][curr->index],active,res,distances,vertices));
        }
    }
    return mx;
}

int main() {
    ifstream f("vertices.txt");
    ifstream g("edges.txt");
    string line;
    vector<vertex*> vertices;
    vector<vertex*> non_zero_vertices;
    vector<vector<int>> distances(54);
    for (int i = 0; i < 54; ++i) {
        distances[i].resize(54);
    }
    int curr = 0;
    while(getline(f,line)) {
        vertex* v = new vertex(line.substr(0,2),stoi(line.substr(3)),curr);
        vertices.push_back(v);
        if (v->val != 0 || v->name == "AA")
            non_zero_vertices.push_back(v);
        ++curr;
    }
    curr = 0;
    while(getline(g,line)) {
        int i = 0;
        while (i < line.size()) {
            string s = line.substr(i,2);
            for (int v = 0; v < vertices.size(); ++v) {
                if (vertices[v]->name == s) {
                    vertices[curr]->neighbors.push_back(vertices[v]);
                }
            }
            i+=2;
        }
        ++curr;
    }
    for (int i = 0; i < non_zero_vertices.size(); ++i) {
        for (int j = 0; j < non_zero_vertices.size(); ++j) {
            if (i!=j) {
                shortestpath(non_zero_vertices[i],non_zero_vertices[j],distances);
            }
        }
    }

    vector<vertex*> active;
    active.push_back(vertices[0]);
    int res = solve(vertices[0],26,active,0,distances,non_zero_vertices);
    cout << res;
}