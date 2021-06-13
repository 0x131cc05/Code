#include <bits/stdc++.h>
using namespace std;

const int N = 52;

double dp[N][N][N], res[N][N][N], fuck[3][N][N][N], tot[N][N][N];

struct RockPaperScissors {
    double bestScore(vector<int> r, vector<int> p, vector<int> s) {
        int n = r.size(); 
        r.insert(r.begin(), 0), p.insert(p.begin(), 0), s.insert(s.begin(), 0);
        for (int t = 0; t <= n; t++) {
            memset(dp, 0, sizeof(dp)), dp[0][0][0] = 1;
            for (int i = 1; i <= n; i++) {
                static double nxt[N][N][N]; memset(nxt, 0, sizeof(nxt));
                for (int a = 0; a < i; a++)
                    for (int b = 0; a + b < i; b++)
                        for (int c = 0; a + b + c < i; c++) if (dp[a][b][c] > 1e-13) {
                            double w = dp[a][b][c] / i;
                            if (i != t) nxt[a][b][c] += w * (i - a - b - c);
                            double tp = w * (a + b + c + 1);
                            int all = r[i] + p[i] + s[i];
                            nxt[a + 1][b][c] += tp * r[i] / all;
                            nxt[a][b + 1][c] += tp * p[i] / all;
                            nxt[a][b][c + 1] += tp * s[i] / all;
                        }
                memcpy(dp, nxt, sizeof(nxt));
            }
            for (int a = n; a >= 0; a--)
                for (int b = n - a; b >= 0; b--)
                    for (int c = n - a - b; c >= 0; c--) {
                        if (!t) { tot[a][b][c] = dp[a][b][c]; continue; }
                        double appear = 1 - dp[a][b][c] / tot[a][b][c];
                        int all = r[t] + p[t] + s[t];
                        fuck[0][a][b][c] += appear * r[t] / all;
                        fuck[1][a][b][c] += appear * p[t] / all;
                        fuck[2][a][b][c] += appear * s[t] / all;
                    }
        }
        for (int a = n; a >= 0; a--)
            for (int b = n - a; b >= 0; b--)
                for (int c = n - a - b; c >= 0; c--) {
                    if (a + b + c == n) continue; 
                    double wkr[3] = { fuck[0][a][b][c], fuck[1][a][b][c], fuck[2][a][b][c] };
                    int remain = n - a - b - c;
                    for (int i = 0; i < 3; i++) wkr[i] /= remain;
                    double nxt[3] = { res[a + 1][b][c], res[a][b + 1][c], res[a][b][c + 1] };
                    double tmp = 0;
                    for (int i = 0; i < 3; i++) {
                        double A = (nxt[i] + 1) * wkr[i];
                        double B = nxt[(i + 1) % 3] * wkr[(i + 1) % 3];
                        double C = (nxt[(i + 2) % 3] + 3) * wkr[(i + 2) % 3];
                        tmp = max(tmp, A + B + C);
                    }
                    res[a][b][c] = tmp;
                }
        return res[0][0][0];
    }
};

int main() {
    RockPaperScissors solver;
    cout << solver.bestScore({100, 100, 100},
{100, 100, 100},
{100, 100, 100}
);
}
