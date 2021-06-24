#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

#define fir first
#define sec second

typedef pair<int, int> P;

template<class T> void read(T &x) {
    x = 0; char c = getchar(); bool type = false;
    while (!isdigit(c)) type |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar(); 
    if (type) x = -x;
}

template<class T, class... Tail> void read(T &x, Tail& ...tail) {
    read(x), read(tail...);
}

typedef long long LL;

LL A[N], B[N], S[N], T[N], P1[N], Q[N], w[N];

set<int> p; vector<P> wkr[N];

int main() {
    int n, m; read(n, m); LL base = 0;
    for (int i = 1; i <= n; i++) read(A[i], S[i], P1[i]), A[i] += A[i - 1];
    for (int i = 1; i <= m; i++) read(B[i], T[i], Q[i]), B[i] += B[i - 1];
    for (int i = 1; i <= m; i++) {
        int pos = upper_bound(A, A + n + 1, T[i] - B[i]) - A;
        if (pos) {
            if (pos <= n) wkr[pos].push_back(P(i, Q[i]));
            else base += Q[i]; 
        }
    }
    for (int i = 1; i <= n; i++) {
        int pos = upper_bound(B, B + m + 1, S[i] - A[i]) - B;
        w[0] += P1[i]; vector<int> upd;
        if (pos <= m) {
            w[pos] -= P1[i];
            if (pos) p.insert(pos), upd.push_back(pos);
        }
        for (auto t : wkr[i]) 
            w[t.fir] += t.sec, p.insert(t.fir), upd.push_back(t.fir);
        sort(upd.begin(), upd.end());
        for (auto t : upd) {
            auto l = p.lower_bound(t), r = l; LL nw = 0;
            while (r != p.end()) {
                nw += w[*r];
                if (nw <= 0) w[*r] = 0, r++;
                else { w[*r] = nw; break; } 
            }
            p.erase(l, r);
        }
    }
    LL ans = w[0] + base;
    for (auto t : p) ans += w[t];
    printf("%lld\n", ans);
}
