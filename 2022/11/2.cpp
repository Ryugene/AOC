#include <bits/stdc++.h>

using namespace std;

class Monkey {
public:
    Monkey(char op, int op_val,int test_number, int truethrow, int falsethrow) {
        this->op = op;
        this->op_val = op_val;
        this->test_number = test_number;
        this->truethrow = truethrow;
        this->falsethrow = falsethrow;
    }
    int inspect = 0;
    vector<long long> items;
    char op;
    long long op_val;
    long long test_number;
    int truethrow;
    int falsethrow;
    
    void operation(int i, bool weird) {
        if (weird) {
            this->items[i] *= this->items[i];
            return;
        }
        if (op == '*')
            this->items[i] *= op_val;
        else
            this->items[i] += op_val;
    }
};

int main() {
    ifstream f("items.txt");
    string line;
    vector<vector<long long>> v_items;
    vector<Monkey> vm;
    while (getline(f,line)) {
        vector<long long> items;
        stringstream ss(line);
        string tmp;
        while (getline(ss,tmp,',')) {
            items.push_back(stoll(tmp));
        }
        v_items.push_back(items);
    }

    Monkey m0('*',5,11,6,5); vm.push_back(m0);
    Monkey m1('+',5,19,6,0); vm.push_back(m1);
    Monkey m2('*',19,5,3,1); vm.push_back(m2);
    Monkey m3('+',7,3,1,0); vm.push_back(m3);
    Monkey m4('+',2,13,2,7); vm.push_back(m4);
    Monkey m5('+',1,17,4,7); vm.push_back(m5);
    Monkey m6('*',69,7,5,4); vm.push_back(m6);
    Monkey m7('+',4,2,3,2); vm.push_back(m7);

    /*Monkey m0('*',19,23,2,3); vm.push_back(m0);
    Monkey m1('+',6,19,2,0); vm.push_back(m1);
    Monkey m2('*',69,13,1,3); vm.push_back(m2);
    Monkey m3('+',3,17,0,1); vm.push_back(m3);*/
    for (int i = 0; i < v_items.size(); ++i) {
        vm[i].items = v_items[i];
    }
    int LCM = 9699690;
    for (int r = 1; r <= 10000; ++r) {
        int monke = 0;
        for (auto&& m : vm) {
            for (int i = 0; i < m.items.size(); ++i) {
                ++m.inspect;
                if (monke == 6)
                    m.operation(i,true);
                else
                    m.operation(i,false);
                
                int new_item = m.items[i] % LCM;
                if (new_item % m.test_number == 0)
                    vm[m.truethrow].items.push_back(new_item);
                
                else
                    vm[m.falsethrow].items.push_back(new_item);
                
            }
            m.items.clear();
            ++monke;
        }/*
        for (int i = 0; i < vm.size(); ++i) {
                cout << "monkey" << i << ":";
                for (int j = 0; j < vm[i].items.size(); ++j) {
                    cout << vm[i].items[j] << ",";
                }
                cout << "inspect:" << vm[i].inspect << endl;
            }
            cout << endl;*/
    }
    int mx1 = 0;
    int mx2 = 0;
    for (int i = 0; i < vm.size(); ++i) {
        if (vm[i].inspect > mx1) {
            mx2 = mx1;
            mx1 = vm[i].inspect;
        }
        else if (vm[i].inspect <= mx1 && vm[i].inspect > mx2)
            mx2 = vm[i].inspect;
    }
    long long ans = (long long)mx1 * (long long)mx2;
    cout << ans;
}