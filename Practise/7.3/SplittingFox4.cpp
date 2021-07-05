#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> P;

const double eps = 1e-7;

vector<int> solve(bitset<201> g) {
    bitset<201> f; f[0] = 1;
    vector<int> res;
    for (int i = 1; i <= 200; i++)
        if (f[i] != g[i]) res.push_back(i), f ^= f << i;
    return res;
}

#define x first
#define y second

int cross(P a, P b) {
    return a.x * b.y - a.y * b.x;
}

P operator- (P a, P b) {
    return P(a.x - b.x, a.y - b.y);
}

int stk[610], top;

bitset<401> dp[310][210], dp1[310][210];

struct SplittingFoxes4 {
    vector<int> construct(vector<int> X, vector<int> Y) {
        vector<P> p; int n = X.size();
        for (int i = 0; i < n; i++) 
            p.push_back(P(X[i], Y[i]));
        sort(p.begin(), p.end());
        P lst = p[0];
        for (auto &t : p) t = t - lst;
        lst = P(0, 0) - lst;
        if (lst.x < 0) return {-1};
        for (int i = 0; i < n; i++) {
            while (top >= 2 && cross(p[i] - p[stk[top - 1]], p[stk[top]] - p[stk[top - 1]]) >= 0)
                top--;
            stk[++top] = i;
        }
        vector<P> ans;
        for (int i = 1; i < top; i++) {
            vector<P> tp;
            P st = p[stk[i]]; 
            for (auto t : p) if (cross(p[stk[i + 1]] - st, t - st) == 0) 
                tp.push_back(t);
            sort(tp.begin(), tp.end()); 
            bitset<201> wkr;
            bool type = tp[1].x == tp[0].x;
            for (auto t : tp) {
                int d = 0;
                if (type) d = t.y - st.y;
                else d = t.x - st.x;
                d = abs(d), wkr[d] = 1;
            }
            auto res = solve(wkr);
            double ratio = type ? 0. : (double)(tp[1].y - tp[0].y) / (tp[1].x - tp[0].x);
            for (auto t : res) {
                int A = t, B = round(t * ratio);
                if (type) swap(A, B);
                ans.push_back(P(A, B));
            }
        }
        sort(ans.begin(), ans.end()), ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
        vector<P> nxt;
        for (auto t : ans) {
            int ct = 1;
            while (t.x % 2 == 0 && t.y % 2 == 0) ct *= 2, t.x /= 2, t.y /= 2;
            for (int i = 1; i <= ct; i++) nxt.push_back(t);
        }
        int cur = 0; dp[0][0][200] = dp1[0][0][200] = 1;
        for (auto t : nxt) {
            cur++;
            for (int i = 0; i <= 200; i++) dp[cur][i] = dp[cur - 1][i], dp1[cur][i] = dp1[cur - 1][i];
            for (int i = 0; i <= 200; i++) if (i + t.first <= 200) {
                if (t.second >= 0) {
                    dp[cur][i + t.first] ^= dp[cur - 1][i] << t.second;
                    dp1[cur][i + t.first] |= dp1[cur - 1][i] << t.second;
                } else {
                    dp[cur][i + t.first] ^= dp[cur - 1][i] >> (-t.second);
                    dp1[cur][i + t.first] |= dp1[cur - 1][i] >> (-t.second);
                }
            }
        }
        int all = 0;
        for (int i = 0; i <= 200; i++)
            for (int j = 0; j <= 400; j++) if (dp[cur][i][j]) 
                all++;
        if (all != p.size()) return {-1};
        for (auto t : p) {
            if (!dp[cur][t.x][t.y + 200]) return {-1};
        }
        if (!dp1[cur][lst.x][lst.y + 200]) return {-1};
        for (int i = cur; i >= 1; i--) {
            P &nw = nxt[i - 1], tmp = lst - nw;
            if (tmp.x >= 0 && dp1[i - 1][tmp.x][tmp.y + 200]) {
                lst = tmp, nw = P(0, 0) - nw;
            }
        }
        vector<int> zjk;
        for (auto t : nxt) zjk.push_back(t.x), zjk.push_back(t.y);
        return zjk;
    }
};
