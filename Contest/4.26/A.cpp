#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int mod, inv2;

typedef long long LL;
typedef pair<int, int> P;

int ans[N][N], mark[N], inv[N * 2], n;

inline void mix(int l, int l1, int r1) {
    for (int i = l; i <= n; i++) 
        for (int j = 0; j <= r1 - l1; j++) if (ans[i][j + l1] != ans[i][r1 - j]) 
            ans[i][j + l1] = ans[i][r1 - j] = (LL)(ans[i][j + l1] + ans[i][r1 - j]) * inv2 % mod;
}

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int dp[N][N], tmp[2][N], hh[N]; // 前面有 i 个偶数段，j 个奇数段

inline void wkr() {
    int nw = 0; vector<vector<P>> fuck;
    while (233) {
        vector<int> seg; vector<P> zjk;
        for (int i = 1; i <= n; i++) if (!mark[i]) {
            int j = i;
            while (j < n && !mark[j + 1]) j++;
            seg.push_back(j - i + 1), i = j;
        }
        sort(seg.begin(), seg.end());
        if (seg.back() <= 2) {
            int t = 0;
            for (auto a : seg) t += a;
            t = Pow(t, mod - 2);
            for (int i = nw + 1; i <= n; i++)
                for (int j = 1; j <= n; j++) if (!mark[j]) ans[i][j] = t;
            break;
        }
        int a = 0, b = 0, t = (seg.back() + 1) / 2;
        for (auto x : seg) if ((x + 1) / 2 == t) {
            if (x & 1) a++; else b++;
        }
        for (int i = 1; i <= n; i++) if (!mark[i]) {
            int j = i;
            while (j < n && !mark[j + 1]) j++;
            if ((j - i + 2) / 2 == t) zjk.push_back(P(i, j));
            i = j;
        }
//        cout << a << ' ' << b << endl;
        memset(dp, 0, sizeof(dp)), memset(tmp, 0, sizeof(tmp)), dp[0][0] = 1;
        for (int i = 0; i <= a; i++) {
            for (int j = 0; j <= b; j++) if (dp[i][j]) {
            	int p = (LL)(a - i) * inv[a - i + (b - j) * 2] % mod;
                int A = (LL)dp[i][j] * p % mod, B = (LL)dp[i][j] * (mod + 1 - p) % mod;
                Inc(tmp[0][nw + i + j + 1], A), Inc(dp[i + 1][j], A);
                Inc(tmp[1][nw + i + j + 1], B), Inc(dp[i][j + 1], B);
            }
        }
//        cout << tmp[0][3] << endl;
        int l[2] = {Pow(a, mod - 2), Pow(b, mod - 2)};
        for (int i = nw + 1; i <= nw + a + b; i++)
            for (auto t : zjk) {
            	int len = t.second - t.first + 1;
            	ans[i][t.first + len / 2] = (LL)l[len & 1 ^ 1] * tmp[len & 1 ^ 1][i] % mod;
			}
        for (auto t : zjk) mark[t.first + (t.second - t.first + 1) / 2] = 1;
        // for (int i = 1; i <= n; i++) cout << ans[2][i] << ' ';
        // cout << endl;
        hh[fuck.size()] = nw, nw += a + b, fuck.push_back(zjk);
    }
    for (int i = fuck.size() - 1; i >= 0; i--) {
        int t = hh[i] + 1;
        for (auto a : fuck[i]) 
            mix(t, a.first, a.second);
    }
}

int main() {
    scanf("%d%d", &n, &mod), inv2 = (mod + 1) / 2;
    for (int i = 1; i <= n * 2; i++) inv[i] = Pow(i, mod - 2);
    wkr();
    for (int i = 1; i <= n; i++, puts(""))
        for (int j = 1; j <= n; j++) {
            printf("%d", ans[i][j]);
            if (j != n) putchar(' ');
        }   
    return 0;
}
