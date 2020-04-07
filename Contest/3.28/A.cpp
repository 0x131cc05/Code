#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int mod = 1e9 + 7;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

map<vector<int>, int> mp;

int G[N][N], tot, n, inc[N][N], p[N], vis[N];

inline int ID(vector<int> &s) {
    if (mp.count(s)) return mp[s];
    return mp[s] = ++tot;
}

inline vector<int> trans(vector<int> &base, int pos) {
    vector<int> res(n), tmp = base; int A = 0, B = 0;
    for (int i = 1; i < n; i++) tmp[i] += tmp[i - 1], A = max(A, tmp[i]);
    for (int i = 0; i < n; i++) {
        // int t = tmp[i] + (i == pos); 
        // if (i) t = max(t, tmp[i - 1] + (i - 1 == pos));
        // if (i < n - 1) t = max(t, tmp[i + 1] + (i + 1 == pos));
        int t = tmp[i]; 
        if (i) t = max(t, tmp[i - 1]);
        if (i < n - 1) t = max(t, tmp[i + 1]);
        if (i == pos) t++;
        res[i] = t, B = max(B, t);
    }
    for (int i = n - 1; i >= 1; i--) res[i] -= res[i - 1];
    res[0] = 0; int s = ID(base), t = ID(res);
    G[s][t] = (G[s][t] + p[pos]) % mod;
    if (A != B) inc[s][t] = (inc[s][t] + p[pos]) % mod;
    return res;
}

void build(vector<int> status) {
    int id = ID(status);
    if (vis[id]) return;
    vis[id] = 1;
    for (int i = 0; i < n; i++) build(trans(status, i));
}

int A[N][N], res[N];

inline void Gauss() {
    for (int i = 1; i < tot; i++)
        for (int j = 1; j <= tot; j++) 
            A[i][j] = G[j][i];
    for (int i = 1; i < tot; i++) 
        A[i][i] = (A[i][i] - 1 + mod) % mod;
    A[tot][tot] = 1, A[tot][tot + 1] = 1;
    for (int i = 1; i <= tot; i++) {
        for (int j = i + 1; j <= tot; j++) if (A[j][i]) {
            swap(A[i], A[j]); break;
        }
        assert(A[i][i]); int inv = Pow(A[i][i], mod - 2);
        for (int j = i + 1; j <= tot; j++) if (A[j][i]) {
            int t = (LL)inv * A[j][i] % mod;
            for (int k = 1; k <= tot + 1; k++) 
                A[j][k] = (A[j][k] - (LL)A[i][k] * t % mod + mod) % mod;
        }
    }
    for (int i = tot; i >= 1; i--) {
        int inv = Pow(A[i][i], mod - 2);
        res[i] = (LL)A[i][tot + 1] * inv % mod;
        for (int j = 1; j < i; j++) if (A[j][i]) 
            A[j][tot + 1] = (A[j][tot + 1] - (LL)res[i] * A[j][i] % mod + mod) % mod, A[j][i] = 0;
    }
//    for (int i = 1; i <= tot; i++) cout << res[i] << ' ';
//    cout << endl;
}

inline int process() {
    int ans = 0, sum = 0;
    for (int i = 1; i <= tot; i++) sum = (sum + res[i]) % mod;
    for (int i = 1; i <= tot; i++) res[i] = (LL)res[i] * Pow(sum, mod - 2) % mod;
//    cout << endl;
    for (int i = 1; i <= tot; i++) {
        for (int j = 1; j <= tot; j++) if (inc[i][j]) 
            ans = (ans + (LL)res[i] * inc[i][j]) % mod;
    }
    return ans;
}

int main() {
    scanf("%d", &n); int inv = Pow(10, mod - 2);
    for (int i = 0; i < n; i++) {
        double t; scanf("%lf", &t);
        p[i] = ((LL)(t * 10 + 0.1)) * inv % mod;
    }
    vector<int> base(n);
    build(base), Gauss(), printf("%d\n", process());
//    cout << tot << endl;
    return 0;
}
