#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

int st[18][N], lg[N], num[N], R[18][N], L[18][N], go[18][N];

int Max(int a, int b) {
    return num[a] > num[b] ? a : b;
}

int get(int l, int r) {
    if (l > r) return 0;
    int len = lg[r - l + 1];
    return Max(st[len][l], st[len][r - (1 << len) + 1]);
}

int stk[N];

int jumpR(int pos, int tar) {
    int res = 0;
    for (int i = 17; i >= 0; i--)
        if (R[i][pos] && R[i][pos] <= tar) res += 1 << i, pos = R[i][pos];
    assert(pos == tar);
    return res;
}

int jumpL(int pos, int tar) {
    int res = 0;
    for (int i = 17; i >= 0; i--)
        if (L[i][pos] && L[i][pos] >= tar) res += 1 << i, pos = L[i][pos];
    assert(pos == tar);
    return res;
}

int n; 

void init(int n, vector<int> h) {
    ::n = n;
    for (int i = 1; i <= n; i++) num[i] = h[i - 1], st[0][i] = i;
    for (int i = 1; i < 18; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++) 
            st[i][j] = Max(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    int top = 1; stk[top] = n;
    for (int i = n - 1; i >= 1; i--) {
        while (top && num[i] > num[stk[top]]) L[0][stk[top--]] = i;
        stk[++top] = i;
    }
    stk[top = 1] = 1;
    for (int i = 2; i <= n; i++) {
        while (top && num[i] > num[stk[top]]) R[0][stk[top--]] = i;
        stk[++top] = i;
    }
    for (int i = 1; i <= n; i++) 
        go[0][i] = Max(L[0][i], R[0][i]);
    for (int i = 1; i < 18; i++)
        for (int j = 1; j <= n; j++) 
            L[i][j] = L[i - 1][L[i - 1][j]], R[i][j] = R[i - 1][R[i - 1][j]], go[i][j] = go[i - 1][go[i - 1][j]];
}

int work(int A, int B) {
    if (get(min(A, B), max(A, B)) != B) return -1;
    int res = 0;
    for (int i = 17; i >= 0; i--) {
        int t = go[i][A];
        if (!t) continue;
        if (get(min(t, B), max(t, B)) != B) continue;
        A = go[i][A], res += 1 << i;
    }
    if (A < B) return res + jumpR(A, B);
    return res + jumpL(A, B);
}

int suf(int L, int R, int x) {
    int l = L, r = R, mid = (l + r) >> 1, pos = L - 1;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (num[get(mid, R)] > x) pos = mid, l = mid + 1;
        else r = mid - 1;
    }
    return pos;
}

int pre(int L, int R, int x) {
    int l = L, r = R, mid = (l + r) >> 1, pos = R + 1;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (num[get(L, mid)] > x) pos = mid, r = mid - 1;
        else l = mid + 1;
    }
    return pos;
}

int work(int A, int C, int D) {
    if (get(A, D) != get(C, D)) return -1;
    int mx = num[get(C, D)];
    int mx1 = get(A + 1, C - 1);
    if (num[mx1] > mx) return -1;
    if (num[A] > num[mx1]) return num[A] < mx ? 1 : -1;
    int t1 = work(A, mx1) + 1, t2 = 1e9; int p = suf(1, A - 1, num[mx1]);
    if (p && num[p] < mx) t2 = work(A, p) + 1;
    if (!t2) t2 = 1e9;
    return min(t1, t2); 
}

int minimum_jumps(int A, int B, int C, int D) {
    A++, B++, C++, D++;
    int mx = num[get(C, D)];
    int pos = suf(A, B, mx) + 1;
    if (pos > B) return -1;
    return work(get(pos, B), C, D);
}

// int main() {
//     init(7, {9, 5, 7, 6, 8, 3, 10, 1, 2, 4});
//     cout << minimum_jumps(1, 1, 6, 6) << endl;
// }