#include <bits/stdc++.h>

using namespace std;

// X vs A | Y vs B | Z vs C draw
// X vs C | Y vs A | Z vs B win
// X vs B | Y vs C | Z vs A lose

int game(string p1, string p2) {
    if ( (p1 == "A" && p2 == "X") || (p1 == "B" && p2 == "Y") || (p1 == "C" && p2 == "Z") )
        return 3;
    else if ( (p1 == "A" && p2 == "Y") || (p1 == "B" && p2 == "Z") || (p1 == "C" && p2 == "X") )
        return 6;
    else return 0;
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
        
        if (p2 == "X") c = 1;
        else if (p2 == "Y") c = 2;
        else c = 3;

        score += game(p1,p2) + c;
    }
    cout << score;
}