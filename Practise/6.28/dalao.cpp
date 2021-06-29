#include <bits/stdc++.h>
using namespace std;

const int N = 2000010;

typedef long long LL;

int A[N], B[N], C[N], id[N], n;

LL seed;

LL rnd() { return seed = ((seed * 19260817) ^ 233333) & ((1 << 24) - 1); }

void gen(int a[]) {
    for (int i = 1; i <= n; i++) a[i] = i;
    for (int i = 1; i <= n; i++) swap(a[i], a[rnd() % i + 1]);
}

int tree[N];

void upd(int x) {
    for (; x <= n; x += x & -x) tree[x]++;
}

void clr(int x) {
    for (; x <= n; x += x & -x) tree[x] = 0;
}

int que(int x) {
    int res = 0;
    for (; x; x -= x & -x) res += tree[x];
    return res;
}

LL res;

struct node {
    int B, C;
    bool operator < (const node &b) const {
        return B < b.B;
    }
} p[N];

void solve(int l, int r) {
    if (r - l <= 20) {
        for (int i = l; i < r; i++)
            for (int j = i + 1; j <= r; j++) 
                if (p[i].B < p[j].B && p[i].C < p[j].C)
                    res++; 
        stable_sort(p + l, p + r + 1);
        return;
    }
    if (l == r) return;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    int cur = l, ct = 0; static node nxt[N];
    for (int i = mid + 1; i <= r; i++) {
        while (cur <= mid && p[cur].B < p[i].B) 
            upd(p[cur].C), nxt[++ct] = p[cur++];
        if (cur != l) res += que(p[i].C);
        nxt[++ct] = p[i];
    }
    for (int i = l; i < cur; i++) clr(p[i].C);
    for (int i = cur; i <= mid; i++) nxt[++ct] = p[i];
    for (int i = l; i <= r; i++) p[i] = nxt[i - l + 1];
}

int main() {
    cin >> n >> seed, gen(A), cin >> seed, gen(B), cin >> seed, gen(C);
    for (int i = 1; i <= n; i++)
        id[A[i]] = i;
    for (int i = 1; i <= n; i++) p[i].B = B[id[i]], p[i].C = C[id[i]];
    solve(1, n);
    cout << res << endl;
}