#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
const int mod = 998244353;

typedef long long LL;
typedef pair<int, int> P;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N << 2];

inline void NTT(vector<int> &a, int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0; i < len; i += mid)
            for (int j = i, t, w = 1; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod)
                t = (LL)w * a[j + (mid >> 1)] % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

inline vector<int> mul(vector<int> A, vector<int> B) {
    int n = A.size() + B.size() - 2, len = 1, l = 0;
    while (len <= n) len <<= 1, l++;
    for (int i = 1; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    vector<int> C(len + 1, 0); A.resize(len + 1), B.resize(len + 1);
    NTT(A, len, 1), NTT(B, len, 1);
    for (int i = 0; i < len; i++) C[i] = (LL)A[i] * B[i] % mod;
    NTT(C, len, 0), C.resize(n + 1);
    return C;
}

char s[N]; int num[N], pre[N], ans[N];

void solve(int l, int r) {
    if (l == r) {
        if (num[l] >= 0) ans[0] += num[l];
        return;
    }
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    int mn = 1e9, lmn = 1e9, rmn = 1e9;
    for (int i = l; i <= r; i++) {
        mn = min(mn, pre[i]);
        if (i <= mid) lmn = min(lmn, pre[i]);
        else rmn = min(rmn, pre[i]);
    }
    vector<int> tmp, tmp1; int len = 0, t1 = 0;
    for (int i = l; i <= mid; i++) len = max(len, pre[i] + (s[i] == '-') - lmn);
    for (int i = mid + 1; i <= r; i++) t1 = max(t1, pre[i] - rmn);
    tmp.resize(len + 1), tmp1.resize(t1 + 1);
    for (int i = l; i <= mid; i++) 
        tmp[len - (pre[i] + (s[i] == '-') - lmn)] += num[i];
    for (int i = mid + 1; i <= r; i++)
        tmp1[pre[i] - rmn]++;
    int delta = rmn - lmn;
    tmp = mul(tmp, tmp1); 
    for (int i = 0; i < tmp.size(); i++) {
        int t = i - len + delta;
        if (t >= 0) ans[t] = (ans[t] + tmp[i]) % mod;
    }
}

int main() {
    int n; scanf("%d%s", &n, s + 1); vector<int> fuck;
    for (int i = 1, t = 0; i <= n; i++) {
        if (s[i] != '-') t++, num[i] = s[i] - '0', fuck.push_back(num[i]), pre[i] = t;
        else t--, pre[i] = t, num[i] = -fuck.back(), fuck.pop_back();
    }
    solve(1, n);
    for (int i = 0; i <= n; i++) 
        ans[i + 1] += ans[i] / 10, ans[i] %= 10;
    for (int i = n, flag = 0; i >= 0; i--) {
        if (flag) printf("%d", ans[i]);
        else if (ans[i]) flag = 1, printf("%d", ans[i]);
    }
}
