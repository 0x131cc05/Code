#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

mt19937 rnd((LL)new char + time(0));

const int N = 1010;

int d[N];

char A[N], B[N];

int main() {
    scanf("%s%s", A, B);
    freopen(A, "r", stdin), freopen(B, "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    printf("%d %d\n", n, m);
    for (int i = 1; i <= m; i++) {
        int a, b, w; scanf("%d%d%d", &a, &b, &w);
        if (w) w = 1;
        printf("%d %d %d\n", a, b, w);
    }
}
