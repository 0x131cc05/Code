#include <bits/stdc++.h>
using namespace std;

const int N = 2510;
const int mod = 1e9 + 7;

typedef long long LL;

int dp[N][6600];

class SimilarNames {
private:
    int trie[N][26], ok[N], ncnt = 0, n, m;
    void insert(string s) {
        int nw = 0;
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            if (!trie[nw][c]) trie[nw][c] = ++ncnt;
            nw = trie[nw][c];
        }
        ok[nw] = 1;
    }

    int pw[9], tp[6600][17]; vector<int> trans[6600];

    void dfs(int dep, int s, int s1) {
        if (dep == m) return trans[s].push_back(s1), void();
        dfs(dep + 1, s + pw[dep], s1), dfs(dep + 1, s + pw[dep] * 2, s1);
        for (int i = 0; i < 3; i++)  // 0: {}, 1: {b}, 2:{a, b}
            dfs(dep + 1, s, s1 + pw[dep] * i);
    }

    int t = 0;

    void dfs(int u) {
        dp[u][0] = 1;
        for (int i = 0; i < 26; i++) if (trie[u][i]) {
            int v = trie[u][i]; dfs(v);
            static int tmp[6600]; memset(tmp, 0, sizeof(tmp));
            for (int s = 0; s < pw[m]; s++) if (dp[u][s])
                for (auto t : trans[s]) {
                    assert(s + t < pw[m]);
                    tmp[s + t] = (tmp[s + t] + (LL)dp[u][s] * dp[v][t]) % mod;
                }
            memcpy(dp[u], tmp, sizeof(tmp));
        }
        if (ok[u]) {
            for (int s = pw[m] - 1; s >= 0; s--) if (dp[u][s])
                for (int i = 1; i <= t; i++) if (~tp[s][i])
                    assert(tp[s][i] > s), dp[u][tp[s][i]] = (dp[u][tp[s][i]] + dp[u][s]) % mod; 
        }
    }

public:
    SimilarNames() {
        memset(trie, 0, sizeof(trie)), memset(ok, 0, sizeof(ok));
        memset(tp, -1, sizeof(tp)), memset(dp, 0, sizeof(dp));
    }

    int count(vector<string> s, vector<int> A, vector<int> B) {
        n = s.size(), m = A.size(), pw[0] = 1;
        for (int i = 1; i <= m; i++) pw[i] = pw[i - 1] * 3;
        dfs(0, 0, 0); 
        for (int i = 0; i < n; i++) insert(s[i]);
        static int tmp[51]; memset(tmp, 0, sizeof(tmp));
        for (int i = 0; i < m; i++) tmp[A[i]] = tmp[B[i]] = 1;
        for (int i = 0; i < n; i++) if (tmp[i]) {
            t++;
            for (int s = 0; s < pw[m]; s++) {
                bool flag = true; int nxt = s;
                for (int j = 0; j < m; j++) if (A[j] == i || B[j] == i) {
                    int c = s / pw[j] % 3;
                    if (c == 2 || (c == 1 && B[j] == i) || (c == 0 && A[j] == i)) {
                        flag = false; break;
                    }
                    nxt += pw[j];
                }
                if (!flag) continue;
                tp[s][t] = nxt;
                // cout << s << ' ' << t << ' ' << tp[s][t] << endl;
            }
        }
        dfs(0);
        int res = dp[0][pw[m] - 1];
        for (int i = 1; i <= n - t; i++) res = (LL)res * i % mod;
        return res;
    }
};

// int main() {
//     SimilarNames solver;
//     cout << solver.count({"ryota", "ryohei", "ryotaro", "ryo", "ryoga", "ryoma", "ryoko", "ryosuke", "ciel", "lun",
//  "ryuta", "ryuji", "ryuma", "ryujiro", "ryusuke", "ryutaro", "ryu", "ryuhei", "ryuichi", "evima"},
// {17, 5, 6, 13, 5},
// {9, 2, 14, 17, 14}) << endl;
// }