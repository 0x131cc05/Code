#include <bits/stdc++.h>
using namespace std;

int G[310][310], g[310][310];

typedef pair<int, int> P;

P get(int lx, int rx, int ly, int ry) {
    memset(g, 0, sizeof(g));
    for (int i = lx + 1; i < rx; i++)
        for (int j = ly + 1; j < ry; j++) {
            for (int t = 0; t <= 2; t++)
                for (int p = 0; p <= 2; p++) if (t | p) g[i][j] ^= g[i - t][j - p];
            g[i][j] ^= G[i - 1][j - 1];
        }
    P pos(rx + 1, ry + 1);
    auto val = [&](int i, int j) {
        int res = G[i][j];
        for (int t = -1; t <= 1; t++)
            for (int p = -1; p <= 1; p++) res ^= g[i - t][j - p];
        return res; 
    };
    for (int i = lx; i <= rx; i++) 
        for (int j = ly; j <= ry; j++)
            if (val(i, j)) pos.first = min(pos.first, i), pos.second = min(pos.second, j);
    return pos;     
}

char s[310];

int main() {
    int n, m; scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        for (int j = 1; j <= m; j++) G[i][j] = s[j] == '#';
    }
    int lx = 1, rx = n, ly = 1, ry = m;
    auto fuck = [&]() {
        int a = 1e9, b = -1e9, c = 1e9, d = -1e9;
        for (int i = lx; i <= rx; i++) 
            for (int j = ly; j <= ry; j++)
                if (G[i][j]) a = min(a, i), b = max(b, i), c = min(c, j), d = max(d, j);
        lx = a, rx = b, ly = c, ry = d;
    };
    for (; rx - lx > 1 && ry - ly > 1; memcpy(G, g, sizeof(g)), fuck()) {
        auto res = get(lx, rx, ly, ry);
        if (res.first == rx + 1) continue; 
        G[res.first][res.second] ^= 1;
        auto tmp = get(lx, rx, ly, ry);
        if (tmp.first == rx + 1) continue; 
        G[res.first][res.second] ^= 1; break;
    }
    for (int i = lx; i <= rx; i++, puts(""))
        for (int j = ly; j <= ry; j++) putchar(G[i][j] ? '#' : '.');
}