#include <bits/stdc++.h>
using namespace std;

const int N = 18;

typedef long long LL;

int G[N][N], n; LL dp[N][1 << N], sum[N][1 << N];

inline void FWT(LL a[], int len) {
    for (int mid = 2; mid <= len; mid <<= 1)
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++)
                a[j + (mid >> 1)] += a[j]; 
}

inline void FWT1(LL a[], int len) {
    for (int mid = 2; mid <= len; mid <<= 1)
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++)
                a[j] += a[j + (mid >> 1)]; 
}

inline void IFWT(LL a[], int len) {
    for (int mid = 2; mid <= len; mid <<= 1)
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++)
                a[j + (mid >> 1)] -= a[j]; 
}

inline void pre() {
    for (int i = 0; i < n; i++) dp[i][1 << i] = 1;
    for (int s = 1; s < 1 << n; s++)
        for (int i = 0; i < n; i++) if (s & 1 << i) if (dp[i][s])
            for (int j = 0; j < n; j++) if (!(s & 1 << j) && G[i][j])
                dp[j][s | 1 << j] += dp[i][s];
    for (int s = 1; s < 1 << n; s++)
        for (int i = 0; i < n; i++) sum[__builtin_popcount(s)][s] += dp[i][s];
    for (int i = 1; i <= n; i++) FWT(sum[i], 1 << n);
}

vector<int> stk; LL ans[1 << N], zjk[1 << N];

void dfs(int cur, int remain) {
    if (remain == 0) {
        static LL wkr[1 << N]; memset(wkr, 0, sizeof(wkr));
        for (int i = 0; i < 1 << n; i++) wkr[i] = 1;
        int tp = 0, st = 0;
        for (auto t : stk) {
            tp += t, st |= 1 << tp - 1;
            for (int i = 0; i < 1 << n; i++) 
                wkr[i] *= sum[t][i];
        }
        IFWT(wkr, 1 << n), ans[st] = wkr[(1 << n) - 1];
    }
    for (int i = cur; i <= n; i++) if (i <= remain) 
        stk.push_back(i), dfs(i, remain - i), stk.pop_back();
}

char s[N + 10]; LL res[1 << N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        for (int j = 0; j < n; j++) G[i][j] = s[j] - '0';
    }
    pre(), dfs(1, n);
    for (int i = 0; i < 1 << n - 1; i++) {
        vector<int> hh; int tot = n;
        for (int j = 0; j < n - 1; j++) if (i & 1 << j) {
            int k = j;
            while (k < n - 2 && (i & (1 << k + 1))) k++;
            hh.push_back(k - j + 2), tot -= k - j + 2, j = k;
        }
        for (int i = 1; i <= tot; i++) hh.push_back(1);
        sort(hh.begin(), hh.end());
        int st = 0, tp = 0;
        for (auto t : hh) tp += t, st |= 1 << tp - 1;
        zjk[i] = ans[st];
        if (__builtin_popcount(i) & 1) zjk[i] = -zjk[i];
    }
    FWT1(zjk, 1 << n - 1);
    for (int i = 0; i < 1 << n - 1; i++) {
        res[i] = zjk[i];
        if (__builtin_popcount(i) & 1) res[i] = -res[i];
    }
    int q; scanf("%d", &q);
    while (q--) {
        scanf("%s", s); int st = 0;
        for (int i = 0; i < n - 1; i++) if (s[i] == '1') st |= 1 << i;
        printf("%lld\n", res[st]);
    }
}
