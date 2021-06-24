#include <bits/stdc++.h>
using namespace std;

const int LEN2 = 12288;
const int MOD1 = 8192;
const int LEN5 = 7812500; // 5 ^ 8
const int MOD2 = 390625;

typedef long long LL;

const LL mod = 1e13;

LL mul(LL x, LL y) {
    return ((x * y - (LL)((long double)x / mod * y + 0.5) * mod) % mod + mod) % mod;
}

struct Matrix {
    LL a[2][2];
    Matrix() { memset(a, 0, sizeof(a)); }
    LL* operator[] (int x) { return a[x]; }
    Matrix operator* (Matrix b) {
        Matrix res;
        for (int k = 0; k < 2; k++)
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++) 
                    res[i][j] = (res[i][j] + mul(a[i][k], b[k][j])) % mod;
        return res;
    }
};

Matrix Pow(Matrix x, LL y) {
    Matrix res; res[0][0] = res[1][1] = 1;
    for (; y; y >>= 1, x = x * x) if (y & 1) res = res * x;
    return res; 
}

LL get(LL pos) {
    Matrix base; base[0][0] = base[0][1] = base[1][0] = 1;
    base = Pow(base, pos - 1);
    return base[0][0]; 
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

LL ans = 1e18;

void solve(LL x, int a, int b) { // mod LEN2 = a, mod LEN5 = b
    LL len = (LL)LEN2 / gcd(LEN2, LEN5) * LEN5;
    LL pos = -1;
    for (LL i = b; i < len; i += LEN5) {
        if (i % LEN2 == a) {
            pos = i; break;
        }
    }
    if (pos == -1) return;
    for (LL i = pos; i < 2e13; i += len) {
        if (get(i) == x) {
            ans = min(ans, i); break;
        }
    } 
}

int F1[LEN2], F2[LEN5];

int main() {
    F1[1] = F2[1] = 1;
    for (int i = 2; i < LEN2; i++) F1[i] = (F1[i - 1] + F1[i - 2]) % MOD1;
    for (int i = 2; i < LEN5; i++) F2[i] = (F2[i - 1] + F2[i - 2]) % MOD2;
    LL x; cin >> x;
    vector<int> A, B;
    for (int i = 0; i < LEN2; i++) if (x % MOD1 == F1[i]) A.push_back(i);
    for (int i = 0; i < LEN5; i++) if (x % MOD2 == F2[i]) B.push_back(i);
    for (auto a : A) for (auto b : B) solve(x, a, b);
    if (ans > 1e17) cout << -1 << endl;
    else cout << ans << endl;
}
