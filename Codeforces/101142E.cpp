#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int mod = 418254373;
const int mod1 = 998244353;

typedef long long LL;
typedef pair<int, int> P;

int Pow(int x, int y, int mod = ::mod) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

const int P1 = 233, P2 = 373;

int pw1[N], pw2[N], inv1[N], inv2[N];

map<P, int> G;

string mp[N], cmd; P tmp[N];

set<P> s;

int main() {
    // freopen("easy.in", "r", stdin), freopen("easy.out", "w", stdout);

    int len; scanf("%d", &len), getchar(), pw1[0] = inv1[0] = pw2[0] = inv2[0] = 1, cmd = "";
    for( int i = 1 ; i <= len ; ++ i ) cmd += getchar();
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) mp[i].resize(m + 10), scanf("%s", &mp[i][0]);
    int tar = 0, fuck = 0, fuck1 = 0;
    for (int i = 1; i <= N - 10; i++) {
        pw1[i] = (LL)pw1[i - 1] * P1 % mod;
        pw2[i] = (LL)pw2[i - 1] * P2 % mod;
        inv1[i] = Pow(pw1[i], mod - 2), inv2[i] = Pow(pw2[i], mod - 2);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j - 1] == 'X') {
                tar++, fuck = (fuck + (LL)pw1[i - 1] * pw2[j - 1]) % mod;
                fuck1 = (fuck1 + (LL)Pow(P1, i - 1, mod1) * Pow(P2, j - 1, mod1)) % mod1;
            }
        }
    }
    int i1 = Pow(P1, mod1 - 2, mod1), i2 = Pow(P2, mod1 - 2, mod1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) if (mp[i][j - 1] == 'X')
            s.insert(P((LL)fuck * inv1[i - 1] % mod * inv2[j - 1] % mod, (LL)fuck1 * Pow(i1, i - 1, mod1) % mod1 * Pow(i2, j - 1, mod1) % mod1));
    int px = 0, py = 0, v = 1, v1 = 1, ct = 1; G[P(0, 0)] = 1;
    auto del = [&](int x, int y) {
        v = (v - (LL)(x < 0 ? inv1[-x] : pw1[x]) * (y < 0 ? inv2[-y] : pw2[y])) % mod;
        v1 = (v1 - (LL)(x < 0 ? Pow(i1, -x, mod1) : Pow(P1, x, mod1)) * (y < 0 ? Pow(i2, -y, mod1) : Pow(P2, y, mod1))) % mod1;
        if (v < 0) v += mod;
        if (v1 < 0) v1 += mod1;
    };
    for (int r = 1, l = 1; r <= len; r++) {
        tmp[r] = P(px, py);
        if (cmd[r - 1] == 'l') py--, v = (LL)v * P2 % mod, v1 = (LL)v1 * P2 % mod1;
        else if (cmd[r - 1] == 'r') py++, v = (LL)v * Pow(P2, mod - 2) % mod, v1 = (LL)v1 * i2 % mod1;
        else if (cmd[r - 1] == 'u') px--, v = (LL)v * P1 % mod, v1 = (LL)v1 * P1 % mod1;
        else if (cmd[r - 1] == 'd') px++, v = (LL)v * Pow(P1, mod - 2) % mod, v1 = (LL)v1 * i1 % mod1;
        if (G[P(px, py)]++ == 0) v++, ct++, v1++;
        while (l < r && ct > tar) {
            if (--G[P(tmp[l].first, tmp[l].second)] == 0) {
                int tx = tmp[l].first - px, ty = tmp[l].second - py;
                del(tx, ty), ct--;
            }
            l++;
        }
        if (s.count(P(v, v1)) && ct == tar) 
            return printf("YES\n%d %d", l, r), 0;
    } 
    puts("NO");
}