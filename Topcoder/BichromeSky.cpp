#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

const int N = 110;

typedef pair<int, int> P;
typedef long long LL;

class BichromeSky {
private:
    int n, m, ok[N][N];
    vector<P> A, B; vector<double> V;

    LL cross(int x1, int y1, int x2, int y2) {
        return (LL)x1 * y2 - (LL)y1 * x2;
    }

    double solve(int s) {
        vector<int> id; static double ang[N];
        for (int i = s + 1; i < n; i++) 
            id.push_back(i), ang[i] = atan2(A[i].y - A[s].y, A[i].x - A[s].x);
        sort(id.begin(), id.end(), [&](int a, int b) {
            return ang[a] < ang[b];
        });
        static double ct[N][N]; memset(ct, 0, sizeof(ct));
        id.insert(id.begin(), s), id.push_back(s);
        for (int i = 0; i < id.size(); i++)
            for (int j = i + 1; j < id.size(); j++) {
                if (i == 0 && j + 1 == id.size()) continue;
                int u = id[i], v = id[j]; ct[i][j] = 1;
                for (int k = i + 1; k < j; k++) {
                    int t = id[k];
                    if (cross(A[v].x - A[u].x, A[v].y - A[u].y, A[t].x - A[u].x, A[t].y - A[u].y) < 0)
                        ct[i][j] *= 1 - V[t];
                }
            }
        static double dp[N][N]; memset(dp, 0, sizeof(dp));
        for (int i = 1; i < id.size(); i++) 
            if (ok[s][id[i]]) dp[0][i] = ct[0][i] * V[id[i]];
        for (int i = 1; i < id.size(); i++)
            for (int j = i + 1; j < id.size(); j++)
                if (ok[id[i]][id[j]]) for (int k = 0; k < i; k++) {
                    if (cross(A[id[j]].x - A[id[k]].x, A[id[j]].y - A[id[k]].y, 
                        A[id[i]].x - A[id[k]].x, A[id[i]].y - A[id[k]].y) >= 0) continue;
                    dp[i][j] += dp[k][i] * ct[i][j] * V[id[j]];
                }
        double res = 0;
        for (int i = 1; i < id.size(); i++)
            res += dp[i][(int)id.size() - 1];
        return res;
    }
public:
    BichromeSky() { memset(ok, 0, sizeof(ok)); }

    double totallyCovered(vector<int> X1, vector<int> Y1, 
        vector<int> p, vector<int> X2, vector<int> Y2) {
        n = X1.size(), m = X2.size();
        vector<int> tmp(n);
        for (int i = 0; i < n; i++) tmp[i] = i;
        sort(tmp.begin(), tmp.end(), [&](int a, int b) {
            if (X1[a] != X1[b]) return X1[a] < X1[b];
            return Y1[a] > Y1[b];
        });
        A.resize(n), B.resize(m), V.resize(n);
        for (int i = 0; i < n; i++) A[i] = P(X1[tmp[i]], Y1[tmp[i]]), V[i] = p[tmp[i]] / 1000.;
        for (int i = 0; i < m; i++) B[i] = P(X2[i], Y2[i]);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) if (i != j) {
                ok[i][j] = true;
                for (int k = 0; k < m; k++) {
                    if (cross(A[j].x - A[i].x, A[j].y - A[i].y, B[k].x - A[i].x, B[k].y - A[i].y) < 0) {
                        ok[i][j] = false; break;
                    }
                }
            }
        double res = 0, nw = 1;
        for (int i = 0; i < n; i++) 
            res += nw * solve(i), nw *= 1 - V[i];
        return res;
    }
};
