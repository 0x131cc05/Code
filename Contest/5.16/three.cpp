#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
const int mod = 1e9 + 7;

typedef pair<int, int> P;
typedef long long LL;
typedef multiset<P>::iterator wen;

P num[N];

int main() {
    freopen("three.in", "r", stdin), freopen("three.out", "w", stdout);
    int n; scanf("%d", &n);
    for (int i = 1, a; i <= n; i++) 
        scanf("%d", &a), num[i] = P(a, i);
    sort(num + 1, num + n + 1); multiset<P> s; int res = 0;
    for (int i = 1; i <= 3; i++) 
        s.insert(P(0, 0)), s.insert(P(n + 1, 0));
    for (int i = n; i >= 1; i--) {
        P nw = P(num[i].second, num[i].first); s.insert(nw);
        wen pos = s.find(nw), tmp1 = pos;
        wen A = --pos, B = --pos, L = --pos, C = ++tmp1, D = ++tmp1, R = ++tmp1;
        res = (res + (LL)(A -> first - B -> first) * (D -> first - C -> first) % mod * num[i].first % mod * A -> second % mod * C -> second) % mod;
        res = (res + (LL)(B -> first - L -> first) * (C -> first - nw.first) % mod * num[i].first % mod * A -> second % mod * B -> second) % mod;
        res = (res + (LL)(R -> first - D -> first) * (nw.first - A -> first) % mod * num[i].first % mod * C -> second % mod * D -> second) % mod;
    }
    printf("%d\n", res);
}
