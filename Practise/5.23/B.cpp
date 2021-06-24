#include <bits/stdc++.h>
using namespace std;

const int N = 8;

typedef long long LL;

int n, k;

LL hsh(array<int, N> a) {
    LL tmp = 0;
    for (int i = 1; i <= n; i++) 
        tmp = (LL)tmp * N + a[i];
    return tmp;
}

map<LL, int> s;

vector<int> res; LL tar;

int mn = 1e9;

vector<int> ans;

void operate(array<int, N> &a, int p) {
    int t = a[p + k - 1];
    for (int j = p + k - 1; j > p; j--) a[j] = a[j - 1];
    a[p] = t;
}

void dfs(array<int, N> a) {
    LL tmp = hsh(a);
    if (s.count(tmp) && s[tmp] <= res.size()) return;
    if (res.size() > mn) return;
    // for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    // cout << endl;
    s[tmp] = res.size();
    if (tmp == tar) {
        ans = res, mn = res.size();
        return;
    }
    for (int i = 1; i <= n - k + 1; i++) {
        auto nxt = a; operate(nxt, i);
        res.push_back(i), dfs(nxt), res.pop_back();
    }
}

vector<int> fuck;

void flip(int a) {
    if (a == n - 1) return fuck.push_back(2), void(); 
    if (a == n) {
        fuck.push_back(1);
        for (int i = 1; i <= n / 2; i++) fuck.push_back(1), fuck.push_back(2);
        fuck.push_back(1);
    }
    int p = n - a;
    for (int i = 1; i <= n - 1 - p + 1; i++) fuck.push_back(1);
    fuck.push_back(2);
    for (int i = 1; i <= p - 1; i++) fuck.push_back(1);
    flip(a + 2);
}

int main() {
    cin >> n >> k;
    array<int, N> base, tmp;
    for (int i = 1; i <= n; i++) {
        base[i] = i; cin >> tmp[i];
    }
    tar = hsh(tmp), dfs(base);
    for (auto t : ans) cout << t << ' ';
    cout << endl;
    for (auto t : ans) {
        operate(base, t);
        for (int i = 1; i <= n; i++) cout << base[i] << ' ';
        cout << endl;
    }
    // cout << "end" << endl;
}