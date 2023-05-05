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
// returns <time,# of ore>
pair<int,int> build_ore(blueprint* bp, int n) {
    int t = 1;
    int ore = 0;
    int opr = 1;
    for (t; t <= 24; ++t) {
        if (bp->ore <= ore) {
            --ore;
            ++opr;
            ore -= bp->ore;
        }
        ore += opr;
        if (opr == n)
            break;
    }
    return make_pair(t+1,ore);
}

int simulate(blueprint* bp, int t, int ore, int opr, int clay, int cpr, int obsidian, int obpr, int geode, int gpr) {
    for (t; t <= 24; ++t) {
        if (bp->geode[0] <= ore && bp->geode[1] <= obsidian) {
            ore -= bp->geode[0];
            obsidian -= bp->geode[1];
            ++gpr;
            --geode;
        }
        else if (bp->obsidian[0] <= ore && bp->obsidian[1] <= clay) {
            ore -= bp->obsidian[0];
            clay -= bp->obsidian[1];
            ++obpr;
            --obsidian;
        }
        else if (bp->clay <= ore) {
            return max(simulate(bp,t+1,ore+opr,opr,clay+cpr,cpr,obsidian+obpr,obpr,geode+gpr,gpr),simulate(bp,t+1,ore+opr-bp->clay,opr,clay+cpr,cpr+1,obsidian+obpr,obpr,geode+gpr,gpr));
        }
        ore += opr;
        clay += cpr;
        obsidian += obpr;
        geode += gpr;
    }
    return geode;
}

int main() {
    ifstream f("input.txt");
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
    int i = 1;
    int res = 0;
    for (auto&& bp : vbp) {
        int temp = 0;
        temp = max(temp,simulate(bp,1,0,1,0,0,0,0,0,0)); 
        temp = max(temp,simulate(bp,build_ore(bp,2).first,build_ore(bp,2).second,2,0,0,0,0,0,0)); 
        temp = max(temp,simulate(bp,build_ore(bp,3).first,build_ore(bp,3).second,3,0,0,0,0,0,0)); 
        temp = max(temp,simulate(bp,build_ore(bp,4).first,build_ore(bp,4).second,4,0,0,0,0,0,0));
        temp = max(temp,simulate(bp,build_ore(bp,5).first,build_ore(bp,5).second,5,0,0,0,0,0,0));
        temp *= i;
        ++i;
        res += temp;
    }
    cout << res;
}