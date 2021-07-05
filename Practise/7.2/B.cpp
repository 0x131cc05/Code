#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

int dp[30][N], st[30], n, k, rgt[30][N];

char s[N];

int work() {
    for (int i = 0; i < 26; i++) st[i] = n + 1;
    for (int i = n; i >= 1; i--) {
        st[s[i] - 'a'] = i;
        vector<int> pos;
        for (int j = 0; j < 26; j++) if (st[j]) pos.push_back(st[j]);
        sort(pos.begin(), pos.end());
        for (int j = 1; j < pos.size(); j++)
            rgt[j - 1][i] = pos[j] - 1;
    }
    memset(dp, -1, sizeof(dp)), dp[0][0] = 0;
    for (int i = 0; i < k; i++) 
        for (int j = 0; j < 26; j++) if (dp[j][i] >= 0)
            for (int l = 0; j + l < 26; l++)
                dp[j + l][i + 1] = max(dp[j + l][i + 1], rgt[l][dp[j][i] + 1]);
    for (int i = 0; i < 26; i++)
        for (int j = 1; j <= k; j++) if (dp[i][j] == n) {
            return i + k;
        }
            
}

struct TreasureOfWinedag {
    int solvePuzzle(int n, int k, int m, int c0, vector<int> c1, vector<int> c2, vector<int> c3, vector<int> c4, string s) {
        int l = s.size();
        for (int i = 0; i < l; i++) ::s[i + 1] = s[i];
        for (int i = l; i < n; i++) {
            int t = (LL)i * c0 % m;
            char c = 'z';
            for (int j = 0; j < 25; j++) 
                if (t >= c3[j] && t <= c4[j] && t % c1[j] == c2[j]) {
                    c = 'a' + j; break;
                }
            ::s[i + 1] = c;
        }
        ::n = n, ::k = k;
        return work();
    }
};
