#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef long long LL;

const LL mod = 194910010019260817ll;

LL mul(LL x, LL y) {
    return ((x * y - (LL)((long double)x / mod * y + 0.5) * mod) % mod + mod) % mod;
}

LL Pow(LL x, int y) {
    LL res = 1;
    for (; y; y >>= 1, x = mul(x, x)) if (y & 1) res = mul(res, x);
    return res;
}

struct wen {

static const int mod = 2017925;

vector<LL> val[mod], hh[mod];

bool count(LL x) {
    int t = x % mod;
    for (auto v : val[t]) if (v == x) return true;
    return false;
}

int qry(LL x) {
    int t = x % mod;
    for (int i = 0; i < val[t].size(); i++) if (val[t][i] == x) return hh[t][i];
    assert(0);
}

void push(LL key, LL x) {
    int t = key % mod;
    val[t].push_back(key), hh[t].push_back(x);
}

} mp;

vector<int> pos[N]; 

LL h[N], pw[N]; int num[N], st[18][N], lg[N], n, tot;

int Max(int a, int b) {
    return num[a] > num[b] ? a : b;
}

void pre() {
    tot = 1, mp.push(0, 1), pos[1].push_back(0);
    for (int i = 1; i <= n; i++) {
        pw[i] = Pow(2, num[i]), h[i] = (h[i - 1] + pw[i]) % mod, st[0][i] = i;
        int id = mp.count(h[i]) ? mp.qry(h[i]) : (mp.push(h[i], ++tot), tot);
        pos[id].push_back(i);
    }
    for (int i = 1; i <= 17; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++) 
            st[i][j] = Max(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
}

int get(int l, int r) {
    int len = lg[r - l + 1];
    return Max(st[len][l], st[len][r - (1 << len) + 1]);
}

int count(LL x, int l, int r) {
    if (!mp.count(x)) return 0;
    int id = mp.qry(x);
    return upper_bound(pos[id].begin(), pos[id].end(), r) - lower_bound(pos[id].begin(), pos[id].end(), l);
}

LL res = 0;

void solve(int l, int r) {
    if (l > r) return;
    res++;
    if (l == r) return void();
    int mid = get(l, r); LL t = pw[mid] * 2 % mod;
    for (int i = 1; i <= 18; i++, t = t * 2 % mod) {
        if (mid - l < r - mid) {
            for (int i = l; i <= mid; i++) 
                res += count((t + h[i - 1]) % mod, mid, r);
        } else {
            for (int i = mid; i <= r; i++)
                res += count((h[i] - t + mod) % mod, l - 1, mid - 1);
        }
    }
    solve(l, mid - 1), solve(mid + 1, r);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    pre(), solve(1, n), printf("%lld\n", res);
}
