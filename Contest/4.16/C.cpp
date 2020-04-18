#include <bits/stdc++.h>
using namespace std;

const int N = 41;
const int mod = 1e9 + 7;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline vector<int> Mul(const vector<int> &A, vector<int> B) {
    vector<int> res(A.size() + B.size() - 1, 0);
    for (int i = 0; i < B.size(); i++)
        for (int j = 0; j < A.size(); j++)
            res[i + j] = (res[i + j] + (LL)B[i] * A[j]) % mod;
    return res;
}

inline vector<int> Div(vector<int> A, vector<int> B) {
    vector<int> res(A.size() - B.size() + 1, 0); int inv = Pow(B.back(), mod - 2);
    for (int i = A.size() - 1; i >= B.size() - 1; i--) {
        int t = (LL)A[i] * inv % mod; res[i - B.size() + 1] = t;
        for (int j = 0; j < B.size(); j++)
            A[i - j] = (A[i - j] - (LL)B[B.size() - j - 1] * t % mod + mod) % mod;
    }
    return res;
}

inline vector<int> Lerp(vector<int> y) { // 代入0, 1, 2, ..., y.size() - 1
    int n = y.size() - 1; vector<int> all = {1};
    for (int i = 0; i <= n; i++) {
        all = Mul(all, {mod - i, 1});
    }
    static int inv[N * N];
    for (int i = 1; i <= n; i++) inv[i] = Pow(i, mod - 2);
    vector<int> res(y.size() - 1, 0);
    for (int i = 0; i <= n; i++) {
        vector<int> tmp = Div(all, {mod - i, 1}); int h = y[i];
        for (int j = 0; j <= n; j++) if (j != i) {
            h = (LL)h * inv[abs(i - j)] % mod;
            if (i < j) h = mod - h;
        }
        for (int i = 0; i < tmp.size(); i++) 
            res[i] = (res[i] + (LL)tmp[i] * h) % mod;
    }
    return res;
}

int G[N][N];

inline int Det(int n) {
    int sgn = 1, res = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) if (G[j][i]) {
            swap(G[i], G[j]), sgn = mod - sgn; break;
        }
        if (!G[i][i]) return 0;
        res = (LL)res * G[i][i] % mod; int inv = Pow(G[i][i], mod - 2);
        for (int j = i + 1; j <= n; j++) {
            int t = (LL)G[j][i] * inv % mod;
            for (int k = 1; k <= n; k++)
                G[j][k] = (G[j][k] - (LL)t * G[i][k] % mod + mod) % mod;
        }
    }
    return (LL)res * sgn % mod;
}

int n;

inline void clr() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) G[i][j] = 0;
}

inline void adde(int from, int to, int w) {
    G[from][to] = (G[from][to] - w + mod) % mod, G[to][from] = (G[to][from] - w + mod) % mod;
    G[from][from] = (G[from][from] + w) % mod, G[to][to] = (G[to][to] + w) % mod;
}

int zjk[3][N][N];

// 0: 1, 1: x, 2: x^n

inline int solve(int x) {
    clr(); int t = Pow(x, n);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            int val = (zjk[0][i][j] + (LL)zjk[1][i][j] * x + (LL)zjk[2][i][j] * t) % mod;
            adde(i, j, val);
        }
    return Det(n - 1);
}

int main() {
//    freopen("data.in", "r", stdin);
    int m, x, y; scanf("%d%d%d%d", &n, &m, &x, &y);
    for (int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c), c--;
        zjk[c][a][b]++, zjk[c][b][a]++;
    }
    int all = (n - 1) + n * (n - 1); vector<int> val;
    for (int i = 0; i <= all; i++) {
        val.push_back(solve(i));
        // cout << "solve: " << i << ' ' << val.back() << endl;
    }
    vector<int> res = Lerp(val);
    int ans = 0;
    for (int i = 0; i < res.size(); i++) {
        int A = i % n, B = i / n;
        if (A <= x && B <= y) ans = (ans + res[i]) % mod;
    }
    printf("%d\n", ans);
    return 0;
}
