#include <bits/stdc++.h>
using namespace std;

template<class T> void read(T &x) {
    x = 0; char c = getchar(); bool flag = false;
    while (!isdigit(c)) flag |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (flag) x = -x;
}

template<class T, typename... Tail> void read(T &x, Tail&... tail) {
   read(x), read(tail...);
}

const int N = 100010;

typedef long long LL;
typedef __int128 LL1;

int ct, num[N], val[N], sz, belong[N], pos[N]; LL base[N];
struct Line { 
    LL k, b;
    LL get(int x) { return x * k + b; }
};

vector<Line> l[N];
int head[N], tail[N];

bool check(Line a, Line b, int x) {
    return b.b - a.b <= x * (a.k - b.k);
}

bool check(Line a, Line b, Line c) {
    return (LL1)(c.b - a.b) * (a.k - b.k) <= (LL1)(b.b - a.b) * (a.k - c.k);
}

void add(int blk) {
    int &head = ::head[blk], &tail = ::tail[blk]; auto &l = ::l[blk];
    pos[blk]++;
    while (head < tail && check(l[head], l[head + 1], pos[blk])) head++;
}

LL dp[N];

void push(int blk) {
    int L = (blk - 1) * sz + 1, R = min(blk * sz, ct);
    for (int i = L; i <= R; i++) dp[i] += val[i] * pos[blk] + base[blk];
    pos[blk] = base[blk] = 0;
}

void rebuild(int blk) {
    int L = (blk - 1) * sz + 1, R = min(blk * sz, ct);
    l[blk].clear(), head[blk] = 0, tail[blk] = -1;
    auto &head = ::head[blk], &tail = ::tail[blk]; auto &l = ::l[blk];
    for (int i = R; i >= L; i--) if (dp[i] < 1e14) {
        Line nw = { val[i], dp[i] };
        while (head < tail && l[tail].b == dp[i]) tail--, l.pop_back();
        while (head < tail && check(l[tail - 1], l[tail], nw)) tail--, l.pop_back(); 
        l.push_back(nw), tail++;
    }
    while (head < tail && check(l[head], l[head + 1], 0)) head++;
}

LL get(int blk) {
    if (!l[blk].size()) return 1e18;
    return l[blk][head[blk]].get(pos[blk]) + base[blk];
}

int main() {
    int n; read(n);
    for (int i = 1; i <= n; i++) 
        read(num[i]), val[++ct] = num[i];
    sort(val + 1, val + n + 1), ct = unique(val + 1, val + n + 1) - val - 1, sz = 100;
    for (int i = 1; i <= ct; i++) belong[i] = (i + sz - 1) / sz;
    memset(dp, 0x3f, sizeof(dp)), dp[1] = 0;
    for (int i = 1; i <= belong[ct]; i++) rebuild(i);
    for (int i = 1, mx = 0; i <= n; i++) {
        int cur = lower_bound(val + 1, val + n + 1, num[i]) - val;
        mx = max(mx, num[i]);
        int blk = belong[cur], l = (blk - 1) * sz + 1, r = min(ct, blk * sz);
        push(blk);
        for (int j = blk + 1; j <= belong[ct]; j++) add(j), base[j] -= num[i];
        for (int j = cur + 1; j <= r; j++) dp[j] += val[j] - num[i];
        LL mn = 1e18;
        for (int j = 1; j < blk; j++) mn = min(mn, get(j)), base[j] += mx - num[i];
        for (int j = l; j < cur; j++) mn = min(mn, dp[j]), dp[j] += mx - num[i];
        dp[cur] = min(dp[cur], mn);
        rebuild(blk);
    }
    LL res = 1e18;
    for (int i = 1; i <= belong[ct]; i++) res = min(res, get(i));
    printf("%lld\n", res);
}