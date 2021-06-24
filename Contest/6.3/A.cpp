#include <bits/stdc++.h>
using namespace std;

const int N = 300010;

typedef long long LL;

LL dp[N]; int nxt[N][26], son[19][N]; LL val[19][N]; const LL INF = (LL)1e18 + 2;

int n, m; char s[N];

LL k[N], mx; int p[N];

inline void pre() {
    static int last[26]; s[0] = 'a';
    for (int i = 0; i <= 18; i++) son[i][n + 1] = n + 1;
    for (int i = 0; i < 26; i++) last[i] = n + 1;
    for (int i = n; i >= 0; i--) 
        memcpy(nxt[i], last, sizeof(last)), last[s[i] - 'a'] = i;
    for (int i = n; i >= 0; i--) {
        dp[i] = val[0][i] = 1, son[0][i] = n + 1; 
        for (int j = 0; j < 26; j++) {
            if (dp[nxt[i][j]] > dp[son[0][i]]) son[0][i] = nxt[i][j], val[0][i] = dp[i];
            dp[i] += dp[nxt[i][j]];
            if (dp[i] > INF) dp[i] = INF;
        }
    }   
    for (int i = 1; i <= 18; i++)
        for (int j = 0; j <= n; j++) {
            son[i][j] = son[i - 1][son[i - 1][j]], val[i][j] = val[i - 1][j] + val[i - 1][son[i - 1][j]];
            if (val[i][j] > INF) val[i][j] = INF;
        }
            
}

inline void output(int u, int son) {
    for (int i = 0; i < 26; i++) if (nxt[u][i] == son) {
        putchar(i + 'a'); return;
    }
}

int main() {
    scanf("%s", s + 1), n = strlen(s + 1), pre(), scanf("%d", &m);
    while (m--) {
        LL k; int p, len = 0; scanf("%lld%d", &k, &p); vector<int> wkr, step, type;
        int nw = 0; k++; 
        if (dp[0] < k) { puts("-1"); continue; }
        while (233) {
            if (k == 1) break; int lst = len;
            for (int i = 18; i >= 0; i--) if (son[i][nw] != n + 1) {
                if (val[i][nw] < k && val[i][nw] + dp[son[i][nw]] >= k) 
                    k -= val[i][nw], nw = son[i][nw], len += 1 << i;
            }
            if (len != lst) wkr.push_back(nw), step.push_back(len - lst), type.push_back(1);
            if (k == 1) break;
            k--; bool flag = false;
            for (int i = 0; i < 26; i++) 
                if (dp[nxt[nw][i]] >= k) {
                    nw = nxt[nw][i], len++, step.push_back(1); break;
                } else k -= dp[nxt[nw][i]];
            wkr.push_back(nw), type.push_back(0);
        }
        p = min(p, len);
        int pos = -1, cur = -1;
        for (int i = 0; i < wkr.size(); i++) {
            if (len >= p && len - step[i] < p) {
                cur = i;
                if (step[i] == 1) pos = i ? wkr[i - 1] : 0;
                else {
                    int jump = len - p; pos = i ? wkr[i - 1] : 0;
                    for (int i = 18; i >= 0; i--)
                        if (jump & (1ll << i)) pos = son[i][pos];
                }
                break;
            } else len -= step[i];
        }
        for (int i = 1; i <= p; i++) {
            if (pos != wkr[cur]) {
                if (type[cur]) output(pos, son[0][pos]), pos = son[0][pos];
                else output(pos, wkr[cur]), pos = wkr[cur], cur++;
            } else {
                if (!type[cur + 1]) output(pos, wkr[cur + 1]), pos = wkr[cur + 1], cur++;
                else output(pos, son[0][pos]), pos = son[0][pos], cur++;
            }
        }
        puts("");
    }
}
