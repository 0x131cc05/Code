#include <bits/stdc++.h>
using namespace std;

const int N = 50010;

char s[N]; int nxt[N];

int main() {
    freopen("border.in", "r", stdin), freopen("border.out", "w", stdout);
    int n, q; scanf("%d%d%s", &n, &q, s + 1);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r), l++, r++;
        int n = r - l + 1; char *t = &s[l - 1];
        nxt[1] = 0;
        for (int i = 2; i <= n; i++) {
            int lst = nxt[i - 1];
            while (lst && t[lst + 1] != t[i]) lst = nxt[lst];
            nxt[i] = lst + (t[i] == t[lst + 1]);
        } 
        printf("%d\n", nxt[n]);
    }
}