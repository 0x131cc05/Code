#include <bits/stdc++.h>
using namespace std;

const int N = 160;

typedef long long LL;

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
    Number mn, sum; // prefix min, sum
    tcurts operator + (tcurts b) { return { min(mn, sum + b.mn), sum + b.sum }; }
    void operator += (tcurts b) { *this = *this + b; } 
} dp[2][N][N];

int k, cur;

int vis[2][N][N];

tcurts dfs(int len, int pre, int st) {
    if (len == 0) return { -pre + k, -pre + k };
    if (vis[st][len][pre] == cur) return dp[st][len][pre];
    vis[st][len][pre] = cur, dp[st][len][pre] = { 0, 0 };
    for (int i = st; i < 10; i++) 
        dp[st][len][pre] += dfs(len - 1, pre + (i == cur - 1), 0);
    return dp[st][len][pre];
}

string work(int digit) {
    cur = digit + 1; 
    tcurts pre = {0, 0}; int len = 1;
    for (len = 1; len; len++) {
        auto res = dfs(len, 0, 1);
        if ((pre + res).mn < 0) break;
        pre += res;
    }
    string ans;
    for (int i = len, s = 0; i >= 1; i--) {
        for (int j = i == len ? 1 : 0; j < 10; j++) {
            int tmp = s + (j == cur - 1);
            auto res = dfs(i - 1, tmp, 0);
            if ((pre + res).mn < 0) {
                ans += j + '0', s = tmp; break;
            }
            pre += res;
        }
    }
    ans.back()--;
    return ans;
}

int main() {
    string ans;
    for (int i = 0; i < 10; i++) {
        scanf("%d", &k); auto res = work(i);
        if (!ans.size() || (res.size() < ans.size() || (res.size() == ans.size() && res < ans)))
            ans = res;
    }
    puts(ans.c_str());
}