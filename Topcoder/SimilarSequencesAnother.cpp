#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int mod = 1e9 + 9;

typedef long long LL;

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

map<vector<int>, int> mp;

vector<int> stk[N * 10];

int ncnt, trans[N * 10][7], dp[N][1 << 9][610];

void dfs(int s) {
    auto nw = stk[s]; rotate(nw.begin(), nw.begin() + 1, nw.end());
    for (int i = 1; i <= 6; i++) {
        nw[4] = i;
        static int buk[7]; memset(buk, 0, sizeof(buk));
        for (auto t : nw) buk[t] = 1;
        buk[0] = 0;
        for (int i = 1; i <= 6; i++) 
            buk[i] += buk[i - 1];
        auto nxt = nw;
        for (auto &t : nxt) t = buk[t];
        if (mp.count(nxt)) trans[s][i] = mp[nxt];
        else trans[s][i] = mp[nxt] = ++ncnt, stk[ncnt] = nxt, dfs(ncnt);
    }
}

int cjz[1 << 9][610][7][8];

int get(int s1, int s, int a, int b) {
    if (~cjz[s1][s][a][b]) return cjz[s1][s][a][b];
    int &s2 = cjz[s1][s][a][b]; s2 = 0;
    auto fuck = stk[trans[s][a]];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            int cur = i * 3 + j;
            if (b == fuck[j - i + 2]) s2 |= s1 & (1 << cur);
            if (j && (s2 & (1 << (cur - 1)))) s2 |= 1 << cur;
            if (i && (s1 & (1 << (cur - 3)))) s2 |= 1 << cur;
            if (i && j && (s1 & (1 << (cur - 4)))) s2 |= 1 << cur;  
        }
    return s2;
}

class SimilarSequencesAnother {
public:
    int getCount(int n, int x) {
        if (n <= 2) {
            int res = 1;
            for (int i = 1; i <= n * 2; i++) res = (LL)res * x % mod;
            return res;
        } 
        memset(cjz, -1, sizeof(cjz));
        vector<int> base(5); mp[base] = ncnt = 1, stk[1] = base, dfs(1);
        for (int i = 1; i <= 2; i++) 
            dp[0][(1 << 9) - 1][trans[trans[1][1]][i]] = i == 1 ? x : (LL)x * (x - 1) % mod;
        for (int i = 0; i < n; i++)
            for (int s1 = 1; s1 < 1 << 9; s1++)
                for (int s = 1; s <= ncnt; s++) if (dp[i][s1][s]) {
                    for (int j = 1; j <= 6 && j <= x; j++) {
                        int w1 = j <= 5 ? 1 : x - 5;
                        if (i + 2 >= n && j != 1) continue;
                        for (int k = 1; k <= 7 && k <= x; k++) {
                            int w2 = k <= 6 ? 1 : x - 6;
                            int nxt = get(s1, s, j, k);
                            if (!nxt) continue;
                            Inc(dp[i + 1][nxt][trans[s][j]], (LL)dp[i][s1][s] * w1 % mod * w2 % mod);
                        }
                    }
                } 
        int res = 0;
        for (int i = 1; i <= ncnt; i++) {
            for (int s = 1; s < 1 << 9; s++) {
                bool flag = false;
                for (int j = 0; j < 3; j++) if ((s & (1 << (j * 4)))) {
                    flag = true; break;
                }
                if (flag) res = (res + dp[n][s][i]) % mod;
            }
        }   
        return res;
    }
};

// int main() {
//     SimilarSequencesAnother solver;
//     cout << solver.getCount(
// 100,
// 123456789
// ) << endl;
// }