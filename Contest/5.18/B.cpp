#include <bits/stdc++.h>
using namespace std;

const int N = 5000010;

int n, m;

struct WEN {

int a[N * 4];

int* operator [] (int x) {
    return a + x * m;
}

} up, down, ans, G;

int q1[N], q2[N], head1, tail1, head2, tail2;

inline void merge(int rt, int ls, int rs, int L, int R) {
    head1 = head2 = 1, tail1 = tail2 = 0;
    for (int i = 1, j = 1; i <= m; i++) {
        while (head1 <= tail1 && up[rs][i] <= up[rs][q1[tail1]]) tail1--;
        while (head2 <= tail2 && down[ls][i] <= down[ls][q2[tail2]]) tail2--;
        q1[++tail1] = i, q2[++tail2] = i;
        while (j <= i && i - j + 1 > up[rs][q1[head1]] + down[ls][q2[head2]]) {
            while (head1 <= tail1 && q1[head1] <= j) head1++;
            while (head2 <= tail2 && q2[head2] <= j) head2++;
            j++;
        }
        ans[rt][i] = max(ans[ls][i], max(ans[rs][i], i - j + 1));
    }
    for (int i = 1; i <= m; i++) {
        up[rt][i] = up[ls][i] + (up[ls][i] == L ? up[rs][i] : 0);
        down[rt][i] = down[rs][i] + (down[rs][i] == R ? down[ls][i] : 0);
    }
}

void build(int rt, int l, int r) {
    int mid = (l + r) >> 1;
    if (l == r) {
        for (int i = 1; i <= m; i++) 
            up[rt][i] = down[rt][i] = ans[rt][i] = G[l][i];
        return;
    }
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
    merge(rt, rt << 1, rt << 1 | 1, mid - l + 1, r - mid);
}

int x, y, start, end;

void flip(int rt, int l, int r) {
    if (l == r) return up[rt][y] = down[rt][y] = ans[rt][y] = G[l][y] ^= 1, void();
    int mid = (l + r) >> 1;
    if (x <= mid) flip(rt << 1, l, mid);
    else flip(rt << 1 | 1, mid + 1, r);
    merge(rt, rt << 1, rt << 1 | 1, mid - l + 1, r - mid);
}

void flip(int rt, int l, int r, int x, int y) {
    ::x = x, ::y = y, flip(rt, l, r);
}

void query(int rt, int l, int r) {
    if (start <= l && r <= end) return merge(0, 0, rt, l - start, r - l + 1), void();
    int mid = (l + r) >> 1;
    if (start <= mid) query(rt << 1, l, mid);
    if (end > mid) query(rt << 1 | 1, mid + 1, r);
}

void query(int rt, int l, int r, int start, int end) {
    ::start = start, ::end = end, query(rt, l, r);
}


template<class T> inline void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
    int q; read(n), read(m), read(q);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            read(G[i][j]);
    build(1, 1, n);
    while (q--) {
        int op, x, y, a, b; read(op), read(x), read(y);
        if (op == 0) flip(1, 1, n, x, y);
        else {
            read(a), read(b);
            for (int i = 1; i <= m; i++) up[0][i] = down[0][i] = ans[0][i] = 0;
            query(1, 1, n, x, a); int res = 0;
            for (int i = y; i <= b; i++) res = max(res, min(ans[0][i], i - y + 1));
            printf("%d\n", res);
        }
    }
}
