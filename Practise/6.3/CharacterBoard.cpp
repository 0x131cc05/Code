#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 9;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int calc(int n, int x) { // x^0 + x^1 + \cdots + x^n
    return (LL)(Pow(x, n + 1) - 1) * Pow(x - 1, mod - 2) % mod;
}

struct CharacterBoard {
    int countGenerators(vector<string> G, int w, int x, int y) {
        set<int> s; 
        int n = G.size(), m = G[0].size(); 
        for (int dx = 0; dx < n; dx++)
            for (int dy = -m + 1; dy < m; dy++) {
                LL diff = (LL)dx * w + dy;
                if (diff <= 0) continue;
                for (int t = 1; (LL)t * t <= diff; t++) if (diff % t == 0) {
                    if (t <= w) s.insert(t);
                    if (diff / t <= w) s.insert(diff / t);
                }
            }  
        int all = 0;
        if (w >= n * m) all = calc(w - n * m, 26);
        auto count = [&](int len) -> int {
            map<int, char> mp;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++) {
                    int pos = ((LL)i * w + j) % len;
                    if (mp.count(pos)) {
                        if (mp[pos] != G[i][j]) return -1;
                    } else {
                        mp[pos] = G[i][j];
                    }
                }
            return mp.size();
        };
        for (auto len : s) {
            if (len >= n * m) all = (all - Pow(26, len - n * m) + mod) % mod;
            int t = count(len);
            if (t == -1) continue;
            all = (all + Pow(26, len - t)) % mod;
        }
        return all;
    } 
};

//int main() {
//    CharacterBoard solver;
//    cout << solver.countGenerators({"abababacac",
// "aaacacacbb",
// "ccabababab"},
//8827,
//104,
//6022);
//}
