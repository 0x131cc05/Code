#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL G[51]; int ct[1 << 25], n, lim;

void dfs(int dep, LL s) {
    if (dep == lim + 1) return ct[s >> lim]++, void();
    dfs(dep + 1, s);
    if (s & (1 << dep - 1)) dfs(dep + 1, s & G[dep]);  
}

LL A[1 << 25];

void dfs1(int dep, LL s, LL x) {
    if (dep == lim) return A[x >> lim]++, void();
    dfs1(dep - 1, s, x);
    if (s & (1ll << dep - 1)) dfs1(dep - 1, s & G[dep], x | (1ll << dep - 1));
}

inline void FWT(LL A[], int len) {
    for (int mid = 2; mid <= len; mid <<= 1)
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++) 
                A[j + (mid >> 1)] += A[j];
}

char s[51];

int main() {
    int n; scanf("%d", &n), lim = n / 2;
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1); 
        for (int j = 1; j <= n; j++) if (s[j] == '1')
            G[i] |= 1ll << j - 1;
    }
    dfs(1, (1ll << n) - 1), dfs1(n, (1ll << n) - 1, 0);
    int all = (1 << (n - lim));
    FWT(A, all);
    LL res = 0;
    for (int i = 0; i < all; i++) res += A[i] * ct[i];
    cout << A[all - 1] << endl;
    printf("%lld\n", res);
}