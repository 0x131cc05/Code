#include <bits/stdc++.h>
using namespace std;

const int N = 310;

bitset<N> G[N], G1[N], tmp, hh, r;

int x[N], res, n;

void dfs(int nw) {
    if (!nw) {
        int w = 1;
        for (int i = 1; i <= n; i++) if (x[i]) w = 4 - w;
        for (int i = 1; i <= n; i++) {
            int tmp = 0;
            for (int j = 1; j <= n; j++) if (x[j]) {
                tmp += G1[i][j];
            }
            tmp += r[i];
            w = w * tmp % 4;
        }
        res = (res + w) % 4;
        return;
    }
    if (hh[nw]) {
        int t = tmp[nw];
        for (int i = nw + 1; i <= n; i++) if (G[nw][i]) t ^= x[i];
        if (t) return;
        x[nw] = 1, dfs(nw - 1);
        x[nw] = 0, dfs(nw - 1);
    } else {
        assert(G[nw][nw]);
        int zzh = tmp[nw];
        for (int i = nw + 1; i <= n; i++) 
            if (G[nw][i]) zzh ^= x[i];
        x[nw] = zzh, dfs(nw - 1);
    }
}

void perm(bitset<N> w) {
    tmp = w ^ r, hh.reset();
    for (int i = 1; i <= n; i++) G[i] = G1[i];
    auto Swap = [&](int a, int b) {
        int t = tmp[a]; tmp[a] = tmp[b], tmp[b] = t;
    };
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) if (G[j][i]) {
            swap(G[j], G[i]), Swap(i, j);
            break;
        } 
        if (!G[i][i]) { hh[i] = 1; continue; } 
        for (int j = i + 1; j <= n; j++) if (G[j][i]) 
            G[j] ^= G[i], tmp[j] = tmp[j] ^ (int)tmp[i];
    }
    dfs(n);
}

char s[N];

int main() {
    srand((long long)new char + time(0));
    freopen("2.in", "r", stdin), freopen("2.out", "w", stdout);
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n), res = 0;
        for (int i = 1; i <= n; i++) r[i] = rand() & 1;
        for (int i = 1; i <= n; i++) {
            scanf("%s", s + 1);
            for (int j = 1; j <= n; j++) 
                G1[i][j] = s[j] - '0';
        }
        vector<bitset<N>> ok;
        bitset<N> fuck;
        for (int i = 1; i <= n; i++) fuck[i] = 1;
        ok.push_back(fuck);
        for (int i = 1; i <= n; i++) 
            fuck.flip(i), ok.push_back(fuck), fuck.flip(i);
        for (auto t : ok) perm(t);
        if ((n + 1) & 1) res = 4 - res;
        res %= 4;
//        cout << res << endl;
        puts(res ? "NO" : "YES"); 
    }
}
