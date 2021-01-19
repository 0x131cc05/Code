#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> P;

const int mod = 1e9 + 7;

unordered_map<LL, int> mp;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int th, tn;

vector<int> osu;

unordered_map<int, vector<int>> fuck;

int F(int h, int n) {
    if (h < n) return 0;
    if (n == h) return 1;
    if (h != th && n == 1) return 0;
    LL nw = (LL)n * (th + 1) + h;
    if (mp.count(nw)) return mp[nw];
    int g = gcd(n, h), res = 0;
    auto solve1 = [&](int c, int t) {
        res = (res + F(h / c / t, n / c)) % mod;
    };
    auto solve = [&](int c) {
        int l = h / c;
        vector<int> tmp = fuck[l];
        for (auto i : tmp) 
            solve1(c, i);
    };
    vector<int> tmp = fuck[g];
    for (auto i : tmp) solve(i);
    if (h == th && n == tn) solve(1);
    return mp[nw] = res;
}

int main() {
//    freopen("B.in", "r", stdin), freopen("B.out", "w", stdout);
    cin >> th >> tn, tn = th / tn;
    for (int i = 1; i <= th / i; i++) if (th % i == 0) {
        osu.push_back(i);
        if (i != th / i) osu.push_back(th / i);
    }
    sort(osu.begin(), osu.end());
    for (auto A : osu) {
        vector<int> tmp;
        for (auto B : osu) {
            if (B > A / B) break;
            if (A % B == 0) {
                if (B != 1) tmp.push_back(B);
                if (A / B != B && A / B != 1) tmp.push_back(A / B);
            }
        }
        fuck[A] = tmp;
    }   
    cout << F(th, tn) << endl;
}
