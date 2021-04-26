#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int c[1010];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d", &c[i]);
    int cur = n, res = 0;
    for (int i = m; i >= 1; i--) {
        res = (res + cur) % mod, cur--;
        for (int j = c[i] - 1; j >= 1; j--) {
            int l1 = c[i] - j;
            vector<int> tmp;
            int sum = l1 - 1; tmp.push_back(sum);
            for (int t = i + 1; t <= m; t++)  
                tmp.push_back(c[t] - 2 - sum), sum += tmp.back();
            cout << "at: " << i << ' ' << j << endl;
            for (auto t : tmp) cout << t << ' ';
            cout << endl;
            int hh = 0;
            for (int t = 0; t < tmp.size(); t++) {
                int w = 1;
                for (int l = 0; l <= t; l++) 
                    w = (LL)w * Pow(t - l + 2, tmp[l]) % mod;
                hh = (hh + w) % mod;
            }
            res = (res + (LL)hh * cur) % mod;
            cur--;
        }
    }
    printf("%d\n", res);
}