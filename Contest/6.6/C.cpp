#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
const int SZ = 1010;

struct WEN {

int tag[N * 2 / SZ + 5], tag1[N * 2];

inline void update(int r, int x) {
    int belong = (r + SZ - 1) / SZ;
    tag[belong - 1] += x, tag1[r] += x;
}

inline int query(int pos) {
    int belong = (pos + SZ - 1) / SZ, res = 0, r = min((int)1e6, belong * SZ), lim = N * 2 / SZ + 1;
    for (int i = belong; i <= lim; i++) res += tag[i];
    for (int i = pos; i <= r; i++) res += tag1[i];
    return res;
}

} A, B;

vector<int> wkr[N], zjk[N], G[N];

int h[N];

inline bool check(int u, int v) { // u > v
    return h[u] == h[v] ? u > v : h[u] > h[v];
}

template<class T> inline void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
    freopen("data3.in", "r", stdin), freopen("out.out", "w", stdout);
    int n, q; read(n), read(q);
    for (int i = 1; i <= n; i++) read(h[i]), A.update(h[i], 1);
    for (int i = 1, a, b; i < n; i++)
        read(a), read(b), G[a].push_back(b), G[b].push_back(a);
    for (int i = 1; i <= n; i++) {
        sort(G[i].begin(), G[i].end(), [](int a, int b) {
            return h[a] > h[b];
        });
        for (auto t : G[i]) if (check(t, i)) 
            wkr[i].push_back(t), B.update(h[i], 1);
    }
    while (q--) {
        int op, a, b; read(op), read(a);
        if (op == 1) {
            read(b); int lst = h[a]; h[a] = b; 
            A.update(lst, -1), A.update(b, 1);
            while (wkr[a].size()) {
                int v = wkr[a].back();
                if (h[v] <= h[a]) {
                    B.update(lst, -1), B.update(h[v], 1);
                    zjk[v].push_back(a), wkr[a].pop_back();
                } else {
                    B.update(lst, -(int)wkr[a].size()), B.update(h[a], wkr[a].size());
                    break;
                }
            }
            while (zjk[a].size()) {
                int v = zjk[a].back();
                B.update(lst, -1), B.update(h[v], 1);
                zjk[v].push_back(a), zjk[a].pop_back();
            }
            vector<int>().swap(zjk[a]);
        } else printf("%d\n", A.query(a) - B.query(a));
    }
}
