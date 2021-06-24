#include <bits/stdc++.h>
using namespace std;

const int N = 110;

struct Number {
    vector<int> num;
    void reset() { num.resize(N), fill(num.begin(), num.end(), 0); }
    void flip() { for (int i = 0; i < N; i++) num[i] = 9 - num[i]; } 
    bool operator < (const Number b) const {  
        if (num[N - 1] != b.num[N - 1]) return num[N - 1] == 9;
        for (int i = N - 2; i >= 0; i--) if (num[i] != b.num[i]) 
            return num[i] < b.num[i];
        return 0;
    }
    Number(int x = 0) {
        reset(); int t = abs(x);
        for (int i = 0; t; i++) 
            num[i] = t % 10, t /= 10;
        if (x < 0) {
            flip();
            for (int i = 0; i < N; i++) {
                if (num[i] != 9) { num[i]++; break; }
                num[i] = 0;
            }
        }
    }
    Number operator + (const Number b) {
        Number res; res.reset();
        for (int i = 0, add = 0; i < N; i++) {
            res.num[i] = num[i] + add + b.num[i];
            add = res.num[i] / 10, res.num[i] %= 10;
        }
        assert(res.num[N - 1] == 0 || res.num[N - 1] == 9);
        return res;
    }
    void operator += (const Number b) { *this = *this + b; }
};

struct tcurts {
    Number mx, sum; // prefix min, sum
    tcurts operator + (tcurts b) { return { max(mx, sum + b.mx), sum + b.sum }; }
    void operator += (tcurts b) { *this = *this + b; } 
} dp[2][2][2][10][N];

int vis[2][2][2][10][N];

double k;

int A, B;

tcurts DP(int len, int lst, int ct, bool flg, bool fk) {
    if (fk) lst = ct = 0;
    if (len == 0) return { fk * A - B, fk * A - B };
    if (vis[flg][fk][ct][lst][len]) return dp[flg][fk][ct][lst][len];
    vis[flg][fk][ct][lst][len] = 1;
    auto &f = dp[flg][fk][ct][lst][len]; f = {-1, 0};
    if (fk) {
        for (int i = flg; i < 10; i++) 
            f += DP(len - 1, 0, 0, 0, 1);
    } else {
        for (int i = flg; i < 10; i++) {
            int nxt = i <= lst ? 0 : ct + 1;
            if (nxt == 2) f += DP(len - 1, 0, 0, 0, 1);
            else f += DP(len - 1, i, nxt, 0, 0);
        }
    }
    return f;
}

int main() {
    freopen("math.in", "r", stdin), freopen("math.out", "w", stdout);
    cin >> k;
    A = 100000, B = round(A * k);
    tcurts pre = {-1, 0}; int len = 1;
    for (len = 1; len; len++) {
        auto res = DP(len, 9, 0, 1, 0);
        if (!((pre + res).mx < 0)) break;
        pre += res;
    }
    int lst = 9, ct = 0, flg = 0;
    for (int i = len, s = 0; i >= 1; i--) {
        for (int j = i == len ? 1 : 0; j < 10; j++) {
            int nxt = j > lst ? ct + 1 : 0;
            auto res = DP(i - 1, j, nxt, 0, nxt == 2 || flg);
            if (!((pre + res).mx < 0)) {
                putchar(j + '0'), lst = j, ct = nxt, flg |= nxt == 2; 
                break;
            }
            pre += res;        
        }
    }
}