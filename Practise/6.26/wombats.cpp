#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
const int M = 210;
const int SZ = 16;

int H[N][M], V[N][M];

struct node {
    int l, r, val[M][M];
} T[N];

int n, m;

void pushup(int rt) {
    int mid = T[rt << 1].r * SZ;
    auto get = [&](int i, int j, int k) {
        return T[rt << 1].val[i][j] + T[rt << 1 | 1].val[j][k] + V[mid][j];
    };
    static int pos[M][M];
    auto trans = [&](int i, int j, int l, int r) {
        int mn = 1e9;
        for (int k = l; k <= r; k++) {
            int w = get(i, k, j);
            if (w < mn) mn = w, pos[i][j] = k;
        }
        T[rt].val[i][j] = mn;
    };
    for (int i = 1; i <= m; i++) 
        trans(i, i, 1, m);
    for (int len = 2; len <= m; len++) {
        for (int i = 1; i + len - 1 <= m; i++) {
            int j = i + len - 1, l = pos[i][j - 1], r = pos[i + 1][j];
            trans(i, j, l, r);
        }
        for (int i = len; i <= m; i++) {
            int j = i - len + 1, l = pos[i - 1][j], r = pos[i][j + 1];
            trans(i, j, l, r);
        }
    }
}

void init(int rt) {
    int l = (T[rt].l - 1) * SZ + 1, r = min(l + SZ - 1, n); 
    for (int i = 1; i <= m; i++) {
        int dis[M]; memset(dis, 0x3f, sizeof(dis)), dis[i] = 0;
        for (int t = l; t <= r; t++) {
            if (t != l) for (int j = 1; j <= m; j++) dis[j] += V[t - 1][j];
            for (int j = 2; j <= m; j++)
                dis[j] = min(dis[j], dis[j - 1] + H[t][j - 1]);
            for (int j = m - 1; j >= 1; j--)
                dis[j] = min(dis[j], dis[j + 1] + H[t][j]);
        }
        for (int j = 1; j <= m; j++)
            T[rt].val[i][j] = dis[j];
    }
}

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r; int mid = (l + r) >> 1;
    if (l == r) return init(rt), void();
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r), pushup(rt); 
}

void upd(int rt, int pos) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (l == r) return init(rt), void();
    if (pos <= mid) upd(rt << 1, pos);
    else upd(rt << 1 | 1, pos);
    pushup(rt);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m; j++) scanf("%d", &H[i][j]);
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= m; j++) scanf("%d", &V[i][j]);
    build(1, 1, (n + SZ - 1) / SZ);
    int q; scanf("%d", &q);
    while (q--) {
        int op, a, b, c; scanf("%d%d%d", &op, &a, &b), a++, b++;
        if (op <= 2) {
            scanf("%d", &c);
            if (op == 1) H[a][b] = c;
            else V[a][b] = c;
            upd(1, (a + SZ - 1) / SZ);
        } else {
            printf("%d\n", T[1].val[a][b]);
        }
    }
}