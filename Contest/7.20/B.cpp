#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef long long LL;

int type[N], pos[N], n;

LL dp[N];

LL sol2(int l, int r) {
    int a = 0, b = 0, p = 1e9, p1 = 0; LL res = 0;
    for (int i = l; i <= r; i++) {
        if (type[i] == type[l]) a++, res -= pos[i], p1 = i;
        else b++, res += pos[i], p = min(p, i);  
    }
    assert(b);
    if (a >= b) return res + pos[p] * (a - b);
    return res - pos[p1] * (b - a);
}

LL sol1() {
    memset(dp, 0x3f, sizeof(dp)), dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int j = i;
        while (j >= 1 && type[j] == type[i]) j--;
        while (j >= 1 && type[j] != type[i]) 
            dp[i] = min(dp[i], min(dp[j - 1], dp[j]) + sol2(j, i)), j--;
    }
    return dp[n];
}

int A[N], B[N];

int main() {
    int a, b; scanf("%d%d", &a, &b);
    for (int i = 1; i <= a; i++) scanf("%d", &A[i]);
    for (int i = 1; i <= b; i++) scanf("%d", &B[i]);
    int tp1 = 1, tp2 = 1; n = a + b;
    for (int i = 1; i <= n; i++) {
        if (tp1 <= a && tp2 <= b) {
            if (A[tp1] < B[tp2]) type[i] = 1, pos[i] = A[tp1], tp1++;
            else type[i] = 2, pos[i] = B[tp2], tp2++;
        } else {
            if (tp1 <= a) type[i] = 1, pos[i] = A[tp1], tp1++;
            else type[i] = 2, pos[i] = B[tp2], tp2++;
        }
    }
    if (A[a] < B[1]) printf("%lld\n", sol2(1, n));
    else printf("%lld\n", sol1());
}
