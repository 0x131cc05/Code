#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

int sa[N], x[N], y[N], c[N], m = 127;

inline void Sort(int n) {
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= n; i++) c[x[i]]++;
    for (int i = 1; i <= m; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
}

inline void build(char s[], int n) {
    for (int i = 1; i <= n; i++) x[i] = s[i], y[i] = i;
    Sort(n);
    for (int k = 1; k < n; k <<= 1) {
        int ct = 0;
        for (int i = n; i >= n - k + 1; i--) y[++ct] = i;
        for (int i = 1; i <= n; i++) if (sa[i] > k) y[++ct] = sa[i] - k;
        Sort(n), memcpy(y, x, sizeof(x)), x[sa[1]] = m = 1;
        for (int i = 2; i <= n; i++)
            x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? m : ++m;
        if (m == n) break;
    }
}

char s[N];

int main() {
    scanf("%s", s + 1); int n = strlen(s + 1); build(s, n);
    for (int i = 1; i <= n; i++) printf("%d ", sa[i]);
}