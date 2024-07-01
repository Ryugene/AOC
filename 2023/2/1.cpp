#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream f("input.txt");
    string line;
    int id = 0;
    int res = 0;
    while (getline(f,line)) {
        ++id;
        int start = 0;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == ':') {
                start = i + 2; break;
            }   
        }
        vector<int> rgb = {0,0,0};
        bool cant = false;
        while (start < line.size() && !cant) {
            int x = 0;
            while (line[start] >= '0' && line[start] <= '9') {
                x *= 10;
                x += (line[start] - '0');
                ++start;
            }
            ++start;
            if (line[start] == 'r') {
                rgb[0] = x;
                start += 3;
            }
            else if (line[start] == 'g') {
                rgb[1] = x;
                start += 5;
            }
            else {
                rgb[2] = x;
                start += 4;
            }
            if (start >= line.size() || line[start] == ';') {
                for (int j = 0; j < 3; ++j) {
                    if (rgb[j] > j+12)
                        cant = true;
                    rgb[j] = 0;
                }
            }
            start += 2;
        }
        if (!cant)
            res += id;
    }
    cout << res;
}