#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const int mod = 1e9 + 7;

typedef long long LL;

int frac[N], inv[N], n, k;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

char s[N];

vector<int> zjk;

inline bool check() {
    vector<int> R = zjk, B, T; 
    for (int i = 1; i <= k; i++) {
        if (R.size() + B.size() + T.size() == 0) return true;
        if (s[i] == 'r') {
            if (R.size()) {
                int t = R.back(); R.pop_back();
                if (t > 1) B.insert(B.begin(), t - 1);
            } else if (T.size()) {
                (*T.rbegin())--;
                if (!T.back()) T.pop_back();
            }
        } else {
            if (B.size()) {
                int t = B.back(); B.pop_back();
                if (t > 1) T.push_back(t - 1);
            } else if (T.size()) {
                (*T.rbegin())--;
                if (!T.back()) T.pop_back();
            }
        }
    }
    return R.size() + B.size() + T.size() == 0;
}

int res = 0;

void dfs(int mn, int mx, int lst) {
    if (mn > n) return;
//    cout << "dfs: " << mn << ' ' << mx << ' ' << lst << endl;
//    cout << "zjk: ";
//    for (auto t : zjk) cout << t << ' ';
//    cout << endl;
    if (!check()) return;
    int w = (LL)C(n - mn + mx - 1, mx - 1) * frac[zjk.size()] % mod;
    for (int i = 0; i < zjk.size(); i++) {
        int j = i;
        while (j + 1 < zjk.size() && zjk[j + 1] == zjk[j]) j++;
        w = (LL)w * inv[j - i + 1] % mod, i = j;
    }
//    cout << res << ' ' << w << endl;
    res = (res + w) % mod;
    for (int i = lst; mn + max(1, 2 * i - 1) <= n; i++) 
        zjk.push_back(i + 1), dfs(mn + max(1, 2 * i - 1) + (zjk.size() != 1), mx + (i + 1) * 2, i), zjk.pop_back();
}

int main() {
    scanf("%d%d%s", &n, &k, s + 1), frac[0] = inv[0] = 1;
    for (int i = 1; i <= 200; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    dfs(0, 1, 0);
    printf("%d\n", res);
}
