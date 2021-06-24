#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
const int LIM = 13;
const int TAIL = 10;

using LL = long long;
using uLL = unsigned long long;

int n;
vector<int> pri, mod, r;

void sieve() {
    for (int i = 3; pri.size() < LIM * 3; i++) {
        bool flag = true;
        for (int j = 2; j * j <= i && flag; j++)
            if (!(i % j)) flag = false;
        if (flag) pri.push_back(i);
    }
}

struct AiAe {

uLL v[(N >> 6) + 10];

AiAe() { memset(v, 0, sizeof(v)); }

void set(int x) { v[x >> 6] |= 1ull << (x & 63); }

uLL& operator [] (int x) { return v[x]; }

};

struct tester {

int mod;
vector<int> t0, t1;
vector<AiAe> ok;

void init(int x, bool t = false) {
    mod = x, t0.resize(mod), t1.resize(mod);
    if (t) ok.resize(mod);
    for (int i = 0; i < mod; i++)
        t0[(LL)i * i % mod] = 1, t1[(LL)i * i * 2 % mod] = 1;
}

bool chk1(int x) { return t0[x]; }
bool chk2(int x) { return t1[x]; }

void WelcomeToOSU(int h[]) {
    vector<int> zenith;
    for (int i = 0; i < mod; i++) if (t0[i]) zenith.push_back(i);
    for (int i = 0; i < r.size(); i++) for (auto v : zenith) 
        ok[(v * (1 + ((n - r[i]) & 1)) + h[r[i] + 1]) % mod].set(i);
}

} wkr[LIM + 1], hh[LIM + 1], base;

char s[N];

void pre(int h[], int mod) {
    for (int i = n, w = 1; i >= 1; i--) 
        h[i] = (h[i + 1] + w * (s[i] & 1)) % mod, w = w * 2 % mod;
}

int hsh[LIM + 1][N], h2[LIM + 1][N], res;

void judge(int l, int r) {
    for (int i = 1; i <= LIM; i++) {
        int mod = ::mod[i - 1], w = (hsh[i][l] - hsh[i][r + 1] + mod) % mod;
        if ((n - r) & 1) {
            if (!wkr[i].chk2(w)) return;
        } else if (!wkr[i].chk1(w)) return;
    }
    res = max(res, r - l + 1);
}

int main() {
//    freopen("ex_decode2.in", "r", stdin);
    scanf("%d%s", &n, s + 1), sieve();
    for (int i = 0; i < LIM; i++) mod.push_back(pri[i] * pri[i + LIM] * pri[i + LIM * 2]);
    for (int i = 1; i <= LIM; i++) 
        wkr[i].init(mod[i - 1]), pre(hsh[i], mod[i - 1]);
    base.init(1 << TAIL);
    for (int i = TAIL; i <= n; i++) if (s[i + 1] != '0' || s[i + 2] != '0') {
        int w = 0;
        for (int j = i - TAIL + 1; j <= i; j++)
            w = w * 2 + (s[j] == '1');
        if (base.chk1(w)) r.push_back(i);
    }
    reverse(r.begin(), r.end()); int all = r.size();
    for (int i = 1; i <= LIM; i++) {
        hh[i].init(pri[i - 1], true);
        pre(h2[i], pri[i - 1]);
        hh[i].WelcomeToOSU(h2[i]);
    }
    for (int i = 1; i <= n; i++) if (s[i] == '1')
        for (int j = i + res; j < i + TAIL && j <= n; j++) judge(i, j);
    for (int i = 1; i <= n; i++) if (s[i] == '1') {
        while (r.size() && r.back() < i + TAIL - 1) r.pop_back();
        if (!r.size()) break;
        int top = (r.size() >> 6) + 1;
        for (int j = 0; j <= top; j++) {
            uLL tmp = hh[1].ok[h2[1][i]][j];
            for (int k = 2; k <= LIM && tmp; k++) tmp &= hh[k].ok[h2[k][i]][j];
            for (; tmp; tmp -= tmp & (-tmp)) {
                int id = (j << 6) + __builtin_ctzll(tmp);
                if (id > r.size()) break;
                judge(i, r[id]); 
            }
        }
    }
    printf("%d\n", res);
}
