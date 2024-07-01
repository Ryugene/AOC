#include <bits/stdc++.h>

using namespace std;

// X = lose -> A = 3 | B = 1 | C = 2
// Y = draw -> A = 1 | B = 2 | C = 3
// Z = win ->  A = 2 | B = 3 | C = 1

int game(string p1, string p2) {
    if (p2 == "X") {
        if (p1 == "A") return 3;
        else if (p1 == "B") return 1;
        else return 2;
    }
    else if (p2 == "Y") {
        if (p1 == "A") return 1;
        else if (p1 == "B") return 2;
        else return 3;
    }
    else {
        if (p1 == "A") return 2;
        else if (p1 == "B") return 3;
        else return 1;
    }
}

int main() {
    ifstream f("input.txt");
    string line;
    string p1;
    string p2;
    int score = 0;
    int c = 0;
    while (getline(f,line)) {
        p1 = line.at(0);
        p2 = line.at(2);
        
        if (p2 == "X") c = 0;
        else if (p2 == "Y") c = 3;
        else c = 6;
        score += game(p1,p2) + c;
    }
    cout << score;
}