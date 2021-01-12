#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize(2)

typedef long long LL;

const int N = 5010;

int fuck[N][N];

class OneDimensionalRobot {
public:
    LL theSum(vector<string> commands1, vector<string> commands2, 
        int mnA, int mxA, int mnB, int mxB) {
        string op;
        for (auto t : commands1) op += t;
        for (auto t : commands2) op += t;
        int mn = 0, mx = 0, nw = 0;
        for (int i = 0; i < op.size(); i++) {
            if (op[i] == 'R') nw++;
            else nw--;
            mx = max(mx, nw), mn = min(mn, nw);
        }
        mn = -mn;
        auto go = [&](int A, int B) {
            if (fuck[A][B]) return fuck[A][B];
            int pos = 0;
            for (int j = 0; j < op.size(); j++) {
                if (op[j] == 'R') pos++;
                else pos--;
                pos = max(pos, -A), pos = min(pos, B);
            }
            return fuck[A][B] = pos;
        };
        LL res = 0;
        for (int i = mnA; i <= mxA; i++) {
            for (int j = mnB; j <= mxB; j++) {
                if (i >= mn && j >= mx) res += fuck[i][j] = nw;
                else if (i == mnA || j == mxB) res += go(i, j);
                else {
                    fuck[i][j] = fuck[i - 1][j + 1] - 1;
                    res += fuck[i][j];
                }
            } 
        }
        return res;
    }
};

int main() {
   OneDimensionalRobot solver;
   cout << solver.theSum({"LRRRRLLLRLRLLLRRLLLRRRLLLLLLRLLRLRRLLRLLLLLRRLLLLR",
"RLLLLRRRLRLLRLRRLRLRRLLRRLRRRRLLLRRLLRRLRRRLLRLRLL",
"RLRRRLLLRLRRLRLLLRLLLLRRRLLRLRRLRRRRRLRLLLLLRLLRLR",
"LLRLRRRLRLLLRLLRRLRLRLRLRRRLLRRRLRRRLRLRLRRLLRLRLR",
"LRRRRRLLLRLLRRLLRRRRLLLLRRRRLRRRLLLRRLLRRRRRRLLRLR",
"LRLLRLRLLLLRLLLRLLRRRRLRRLLLLRRRLRRLRLRRLLLRLRLRLR"},
{},
1,
608,
1,
608) << endl;
}
