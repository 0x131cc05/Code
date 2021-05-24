#include <bits/stdc++.h>
using namespace std;

const int N = 10000010;

typedef long long LL;

int num[N];

template<class T> void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

bool flag;

LL res = 0;

void solve(int m) {
    if (m == 0) return; 
    for (int i = m - 1; i > 0; i--) num[i] -= num[i - 1];
    for (int i = 2 * m - 1; i > m; i--) num[i] -= num[i - 1];
    for (int i = 1; i < m; i++) {
        int d = num[i] - num[i + m];
        if (d & 1) return flag = false, void();
        res += abs(d) / 2, num[i] = (num[i] + num[i + m]) >> 1;
        if (d < 0) num[0] += d / 2; else num[m] -= d / 2;
    }
    res += abs(num[0] - num[m]), num[0] = min(num[0], num[m]);
    for (int i = 1; i < m; i++) num[i] += num[i - 1];
    solve(m >> 1);
}

int main() {
    int T; read(T);
    while (T--) { 
        int n, m; read(n), read(m); 
        for (int i = 0; i < n; i++) read(num[i]); 
        flag = true; 
        for (int i = m * 2; i < n; i++) 
            if (num[i] != num[i & (m * 2 - 1)]) 
                flag = false;
        res = 0;
        if (flag) solve(m);
        if (num[0] < 0) flag = false;
        if (!flag) puts("-1");
        else printf("%lld\n", res);
    }
}