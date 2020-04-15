#include <bits/stdc++.h>
using namespace std;

const int N = 10000010;

char s[N]; int nxt[N], ok[N], n;

inline void Just_DOIT(int l, int r) {
    nxt[l] = 0;
    for (int i = l + 1; i <= r; i++) {
        int t = nxt[i - 1];
        while (t && s[l + t] != s[i]) t = nxt[l + t - 1];
        nxt[i] = t + (s[l + t] == s[i]);
    }
    int period = r - l + 1 - nxt[r];
    for (int i = 1; i <= r - l + 1 && i <= n; i++) if ((i - 1) % period) 
        ok[n - i] = 1;
}

int main() {
//    freopen("ex_data2.in", "r", stdin);
    while (~scanf("%s", s + 1)) {
        n = strlen(s + 1);
        for (int i = n + 1; i <= n * 2; i++) s[i] = s[i - n];
        for (int i = 0; i <= n; i++) ok[i] = 0;
        for (int i = 1, j; (j = i) <= n * 2; i = j + 1) {
            while (j < n * 2 && s[j + 1] != s[j]) j++;
            Just_DOIT(i, j);
        }
        for (int i = 0; i < n; i++) putchar(ok[i] + '0');
        puts("");
    }
}
