#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

typedef pair<int, int> P;

template<class T> void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

template<class T, typename... Tail> void read(T &x, Tail&... tail) {
    read(x), read(tail...);
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int num[N], pre[19][N], suf[19][N];

int main() {
    int n; read(n);
    for (int i = 1; i <= n; i++) read(num[i]), pre[0][i] = suf[0][i] = num[i];
    for (int i = 1; i <= 18; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            pre[i][j] = gcd(pre[i - 1][j], pre[i - 1][j + (1 << i - 1)]);
        for (int j = 1 << i; j <= n; j++) 
            suf[i][j] = gcd(suf[i - 1][j], suf[i - 1][j - (1 << i - 1)]);
    }
    vector<P> res;
    for (int i = 1; i <= n; i++) {
        int l = i - 1, r = i + 1;
        for (int t = 18; t >= 0; t--) if (l >= (1 << t)) 
            if (suf[t][l] % num[i] == 0) l -= 1 << t;
        for (int t = 18; t >= 0; t--) if (r + (1 << t) - 1 <= n)
            if (pre[t][r] % num[i] == 0) r += 1 << t;
        res.push_back(P(l - r + 2, l + 1));
    }
    sort(res.begin(), res.end()), res.resize(unique(res.begin(), res.end()) - res.begin());
    while (res.back().first != res[0].first) res.pop_back();
    printf("%d %d\n", (int)res.size(), -res[0].first);
    for (int i = 0; i < res.size(); i++) printf("%d ", res[i].second);
    return 0;
}