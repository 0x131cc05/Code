#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int mod = 998244353;

typedef long long LL;

int num[N], n, tot;
bool cmp(int a, int b) {
    int len = min(tot - a + 1, tot - b + 1);
    for (int i = 1; i <= len; i++) 
        if (num[a + i - 1] != num[b + i - 1])
            return num[a + i - 1] < num[b + i - 1];
    return b >= a;
}

int rk[N], st[18][N], lg[N], id[N];
int Min(int a, int b) { return rk[a] < rk[b] ? a : b; }
void build() {
    for (int i = n + 1; i <= 2 * n; i++) num[i] = num[i - n];
    tot = 2 * n;
    for (int i = 1; i <= n; i++) id[i] = i;
    sort(id + 1, id + n + 1, cmp);
    for (int i = 1; i <= n; i++) rk[id[i]] = i;
    for (int i = 1; i <= n; i++) st[0][i] = i;
    for (int i = 1; i <= 17; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            st[i][j] = Min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
}
int get(int l, int r) {
    int len = lg[r - l + 1];
    return Min(st[len][l], st[len][r - (1 << len) + 1]);
}

int L, R;

bool cmp1(int a, int b) {
    int len = R - L + 1;
    for (int i = 1; i <= len; i++) {
        if (a == R + 1) a = L;
        if (b == R + 1) b = L;
        if (num[a] != num[b]) return num[a] < num[b];
        a++, b++;
    }
    return false;
}

struct wen {
    int v, pos, l, r;
    bool operator < (const wen &b) const {
        return v > b.v;
    }
};

int nxt(priority_queue<wen> &q, vector<int> &A, int &head, int l, int r) {
    auto pushA = [&]() {
        int a = q.top().pos, l1 = q.top().l, r1 = q.top().r, v; q.pop();
        if (l1 < a) v = get(l1, a - 1), q.push((wen){ rk[v], v, l1, a - 1 });
        if (a < r1) v = get(a + 1, r1), q.push((wen){ rk[v], v, a + 1, r1 });
        return a;
    };
    auto pushB = [&]() {
        return A[head++];
    };
    if (q.size() && head < A.size()) {
        int a = q.top().pos, b = A[head]; L = l, R = r;
        if (cmp1(a, b)) return pushA();
        return pushB();
    }
    if (q.size()) return pushA();
    return pushB();
}

int solve(int l1, int r1, int l2, int r2) {
    priority_queue<wen> A, B; vector<int> tailA, tailB;
    for (int i = max(l1, r1 - 20); i <= r1; i++) tailA.push_back(i);
    for (int i = max(l2, r2 - 20); i <= r2; i++) tailB.push_back(i);
    L = l1, R = r1, sort(tailA.begin(), tailA.end(), cmp1);
    L = l2, R = r2, sort(tailB.begin(), tailB.end(), cmp1);
    int t1 = r1 - 21, t2 = r2 - 21, len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
    if (l1 <= t1) {
        int p = get(l1, t1);
        A.push((wen){ rk[p], p, l1, t1 });
    }
    if (l2 <= t2) {
        int p = get(l2, t2);
        B.push((wen){ rk[p], p, l2, t2 });
    }
    t1 = t2 = 0;
    for (int i = 1; i <= min(r1 - l1 + 1, r2 - l2 + 1); i++) {
        int a = nxt(A, tailA, t1, l1, r1), b = nxt(B, tailB, t2, l2, r2);
        int c1 = a == l1 ? num[r1] : num[a - 1], c2 = b == l2 ? num[r2] : num[b - 1];
        if (c1 != c2) return c1 < c2 ? -1 : 1;
    }
    if (len1 != len2) return len1 < len2 ? -1 : 1;
    return 0;
}

int A;

int main() {
    int m; scanf("%d%d%d", &n, &m, &A);
    auto nxt = [&]() {
        return A = ((LL)A * 100000005 + 20150609) % mod;
    };
    for (int i = 1; i <= n; i++) num[i] = nxt() % 2;
    build();
    for (int i = 1; i <= m; i++) {
        int l1 = 1 + nxt() % n, r1 = 1 + nxt() % n, l2 = 1 + nxt() % n, r2 = 1 + nxt() % n;
        if (l1 > r1) swap(l1, r1); if (l2 > r2) swap(l2, r2);
        printf("%d\n", solve(l1, r1, l2, r2));
    }
}