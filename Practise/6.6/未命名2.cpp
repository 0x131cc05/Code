#include <bits/stdc++.h>

#define fi first
#define se second
#define DB double
#define U unsigned
#define P std::pair
#define LL long long
#define LD long double
#define pb emplace_back
#define MP std::make_pair
#define SZ(x) ((int)x.size())
#define all(x) x.begin(), x.end()
#define CLR(i, a) memset(i, a, sizeof(i))
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define ROF(i, a, b) for (int i = a; i >= b; --i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2000 + 5;
const int ha = 998244353;

std::vector<int> G[MAXN];
int n, k;

inline void add(int &x, int y) {
    x += y - ha;
    x += x >> 31 & ha;
}

int dfn[MAXN], low[MAXN], st[MAXN], bel[MAXN], tp, tot;
bool ins[MAXN];
std::vector<int> S[MAXN];

inline void dfs(int v) {
    static int ts = 0;
    dfn[v] = low[v] = ++ts;
    st[++tp] = v;
    ins[v] = 1;
    for (auto x : G[v]) {
        if (!dfn[x]) {
            dfs(x);
            low[v] = std::min(low[v], low[x]);
        } else if (ins[x])
            low[v] = std::min(low[v], dfn[x]);
    }
    if (dfn[v] == low[v]) {
        int t = -1;
        ++tot;
        do {
            t = st[tp--];
            ins[t] = 0;
            S[tot].pb(t);
            bel[t] = tot;
        } while (t != v);
    }
}

std::vector<P<int, int> > trans[MAXN];
std::vector<int> vec;
int ps[MAXN], tmp[MAXN];

int sm[MAXN][MAXN], f[MAXN][MAXN], m;

inline void fix(int &x) {
    while (x < 0) x += m;
    while (x >= m) x -= m;
}

inline void add(int l1, int r1, int l2, int r2, int d) {
    fix(l1);
    fix(r1);
    fix(l2);
    fix(r2);
    if (l1 > r1) {
        add(l1, m - 1, l2, r2, d);
        add(0, r1, l2, r2, d);
        return;
    }
    if (l2 > r2) {
        add(l1, r1, l2, m - 1, d);
        add(l1, r1, 0, r2, d);
        return;
    }
    add(sm[l1][l2], d);
    add(sm[l1][r2 + 1], ha - d);
    add(sm[r1 + 1][l2], ha - d);
    add(sm[r1 + 1][r2 + 1], d);
}

inline void gao(int now) {  // 圈内转移 now
    m = SZ(S[now]);
    if (m == 1) {
        if (k == 1)
            f[S[now][0]][S[now][0]] = 0;
        return;
    }
    std::vector<int> vec;
    vec.pb(S[now][0]);
    while (true) {
        int v = vec.back();
        for (auto x : G[v])
            if (bel[x] == now) {
                v = x;
                break;
            }
        if (v == vec[0])
            break;
        vec.pb(v);
    }
    assert(SZ(vec) == m);
    FOR(i, 0, m - 1) ps[vec[i]] = i;
    goto fuck;
    return;
    
    // 处理 (now,x>now), 只需要枚举 now 转了几圈
    FOR(pre, now + 1, tot) {  // (now,pre)
        for (auto x : S[pre]) {
            FOR(i, 0, m - 1) tmp[i] = f[vec[i]][x];
            // i: circle index
            // i+1 -> i, (#circle)+1 <= k
            // oth -> i, (#circle)+2 <= k
            // (#circie) >= 0
            int sm = 0;
            FOR(i, 0, m - 1) add(sm, tmp[i]);
            sm = 1ll * sm * (k - 1) % ha;
            FOR(i, 0, m - 1) f[vec[i]][x] = (sm + tmp[(i + 1) % m]) % ha;
        }
    }   

    FOR(pre, now + 1, tot) {  // (pre,now)
        for (auto x : S[pre]) {
            FOR(i, 0, m - 1) tmp[i] = f[x][vec[i]];
            // i: circle index
            // i+1 -> i, (#circle)+1 <= k
            // oth -> i, (#circle)+2 <= k
            // (#circie) >= 0
            int sm = 0;
            FOR(i, 0, m - 1) add(sm, tmp[i]);
            sm = 1ll * sm * (k - 1) % ha;
            FOR(i, 0, m - 1) f[x][vec[i]] = (sm + tmp[(i + 1) % m]) % ha;
        }
    }
    fuck:

    FOR(i, 0, m + 2) FOR(j, 0, m + 2) sm[i][j] = 0;

    // 处理 (now,now)
    FOR(i, 0, m - 1) {
        FOR(j, 0, m - 1) {
            int t = f[vec[i]][vec[j]];
            // (x,y)
            if (i == j) {
                if (k > 1) {
                    /*
                     * 一般情况:
                     * 1. x+y+2 <= k
                     * 2. x+y > 0
                     * 方案数: k(k-1)/2 - 1
                     * 边界: 至少有一个 i-1, 此时限制 2 无效
                     */
                    add(0, m - 1, 0, m - 1, 1ll * k * (k - 1) / 2 % ha * t % ha);
                    add(i, i - 2, i, i - 2, ha - t);
                }
                continue;
            }
            if (k == 1) {
                // (i,j) -> (j-1,i-1)
                add(j - 1, j - 1, i - 1, i - 1, t);
                continue;
            }
            /*
             * 一般情况:
             * 1. x+y+2 <= k
             * 2. x+y > 0
             * 方案数: k(k-1)/2 - 1
             * 边界:
             * 1. i->i-1 或 j->j-1 限制 2 失效
             * 2. i->(<j), j->(<i) 限制 1 放宽 1
             * 3. i->(>=j-1), j->(>=i-1) 限制 2 失效, 注意和边界1的影响
             */
            add(0, m - 1, 0, m - 1, 1ll * k * (k - 1) / 2 % ha * t % ha);
            add(i, i - 2, j, j - 2, ha - t);
            if (i != j) {
                add(i, j - 1, j, i - 1, 1ll * k * t % ha);
                add(j - 1, i - 2, i - 1, j - 2, t);
            }
            
        }
    }

    FOR(i, 1, m - 1) FOR(j, 0, m - 1) add(sm[i][j], sm[i - 1][j]);
    FOR(i, 0, m - 1) FOR(j, 1, m - 1) add(sm[i][j], sm[i][j - 1]);
    FOR(i, 0, m - 1) FOR(j, 0, m - 1) f[vec[i]][vec[j]] = sm[i][j];
}

int main() {
    freopen("travel.in", "r", stdin);
    int m;
    scanf("%d%d%d", &n, &m, &k);
    FOR(i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].pb(v);
    }
    if (!k) {
        puts("0");
        return 0;
    }
    FOR(i, 1, n) G[n + 1].pb(i), G[i].pb(0);
    G[n + 1].pb(0);
    FOR(i, 0, n + 1) if (!dfn[i]) dfs(i);

    FOR(i, 0, n + 1) FOR(j, 0, n + 1) trans[std::min(bel[i], bel[j])].pb(i, j);

    f[n + 1][n + 1] = 1;

    ROF(k, tot - 1, 1) {
        // 圈外转移:
        // (?,?) -> (?,k)
        for (auto v : trans[k + 1]) {
            for (auto x : G[v.se])
                if (bel[x] == k)
                    add(f[v.fi][x], f[v.fi][v.se]);
        }
        // (?,k) -> (k,k)
        for (auto v : trans[k]) {
            if (bel[v.fi] == k)
                continue;
            for (auto x : G[v.fi])
                if (bel[x] == k)
                    add(f[x][v.se], f[v.fi][v.se]);
        }
        // (?,?) -> (k,?)
        for (auto v : trans[k + 1]) {
            for (auto x : G[v.fi])
                if (bel[x] == k)
                    add(f[x][v.se], f[v.fi][v.se]);
        }

        if (k > 1)
            gao(k);  // 圈内转移,注意0是没有限制的
    }
    printf("%d\n", f[0][0]);
    return 0;
}
