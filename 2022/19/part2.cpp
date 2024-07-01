#include <bits/stdc++.h>

using namespace std;

class blueprint {
public:
    blueprint(int o, int c, vector<int> ob, vector<int> g) {
        ore = o;
        clay = c;
        obsidian = ob;
        geode = g;
    }
    int ore;
    int clay;
    vector<int> obsidian;
    vector<int> geode;
};


int simulate(blueprint* bp, int t, int ore, int opr, int clay, int cpr, int obsidian, int obpr, int geode, int gpr, bool b_c) {
    for (t; t <= 32; ++t) {
        if (bp->geode[0] <= ore && bp->geode[1] <= obsidian) {
            return simulate(bp,t+1,ore+opr-bp->geode[0],opr,clay+cpr,cpr,obsidian+obpr-bp->geode[1],obpr,geode+gpr,gpr+1,true);
            
        }
        else if (bp->obsidian[0] <= ore && bp->obsidian[1] <= clay) {
                return simulate(bp,t+1,ore+opr-bp->obsidian[0],opr,clay+cpr-bp->obsidian[1],cpr,obsidian+obpr,obpr+1,geode+gpr,gpr,true);
        }
        else if (bp->clay <= ore && b_c) {
            return max(simulate(bp,t,ore,opr,clay,cpr,obsidian,obpr,geode,gpr,false),
                    simulate(bp,t+1,ore+opr-bp->clay,opr,clay+cpr,cpr+1,obsidian+obpr,obpr,geode+gpr,gpr,true));
        }
        else if (bp->ore <= ore && opr < 4) {
            return max(simulate(bp,t+1,ore+opr,opr,clay+cpr,cpr,obsidian+obpr,obpr,geode+gpr,gpr,true),
                    simulate(bp,t+1,ore+opr-bp->ore,opr+1,clay+cpr,cpr,obsidian+obpr,obpr,geode+gpr,gpr,true));
        }
        ore += opr;
        clay += cpr;
        obsidian += obpr;
        geode += gpr;
    }
    return geode;
}

int main() {
    ifstream f("input2.txt");
    string line;
    vector<blueprint*> vbp;
    while (getline(f,line)) {
        stringstream ss; ss << line;
        vector<int> nums;
        int n;
        line.clear();
        while (!ss.eof()) {
            ss >> line;
            if (stringstream(line) >> n)
                nums.push_back(n);
            line.clear();
        }
        vector<int> obsidian = {nums[2],nums[3]};
        vector<int> geode = {nums[4],nums[5]};
        blueprint* bp = new blueprint(nums[0],nums[1],obsidian,geode);
        vbp.push_back(bp);
    }
    int res = 1;
    for (auto&& bp : vbp) {
        int temp = 0;
        temp = simulate(bp,1,0,1,0,0,0,0,0,0,true);
        res *= temp;
    }
    cout << res;
}