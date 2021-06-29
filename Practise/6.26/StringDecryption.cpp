#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

typedef pair<int, int> P;

const int mod = 1e9 + 9;

struct status {
    int lst, len;
    bool operator< (const status &b) const {
        if (lst != b.lst) return lst < b.lst;
        return len < b.len;
    }
} pool[35];

int tot;

map<status, int> ID;

vector<P> append(int id, int ct, int x, bool tag) { // tag: ct 是否不小于 mod
    int lst = pool[id].lst, len = pool[id].len;
    if (!len && !x) return {};
    vector<P> trans;
    trans.push_back(P(ID[{ lst, tag ? 2 : min(len + ct, 2) }], 1)); // 整体加入当前段，不划分
    if (x != lst && (len + ct >= 2 || tag))
        trans.push_back(P(ID[{ x, 0 }], 1)); // 整体加入当前段，在结尾划分
    int remain = ct - 1 - (len == 0);
    if ((tag || remain > 0) && x && x != lst) { // 在中间划分
        trans.push_back(P(ID[{ x, 1 }], 1)); // 在倒数第二个位置划分
        trans.push_back(P(ID[{ x, 2 }], remain - 1)); // 在倒数第二个位置之前划分
    } 
    return trans;
}

int dp[35][510];

struct StringDecryption {
    int decrypt(vector<string> code) {
        string s = " ";
        for (auto t : code) s += t;
        for (int i = -1; i <= 9; i++) 
            for (int j = 0; j <= 2; j++)
                tot++, pool[tot] = { i, j }, ID[pool[tot]] = tot;
        dp[ID[{ -1, 0 }]][0] = 1;
        int n = (int)s.size() - 1;
        for (int i = 2; i <= n; i++)
            for (int j = 0; j <= i - 2; j++) if (s[j] != s[i] && s[j + 1] != '0') {
                bool tag = false; int ct = 0;
                for (int k = j + 1; k < i; k++) {
                    LL nxt = ct * 10ll + (s[k] - '0');
                    if (nxt >= mod) tag = true;
                    ct = nxt % mod;
                }
                for (int t = 1; t <= tot; t++) if (dp[t][j]) {
                    auto trans = append(t, ct, s[i] - '0', tag);
                    for (auto v : trans) 
                        dp[v.first][i] = (dp[v.first][i] + (LL)v.second * dp[t][j]) % mod;
                }
            }
        int res = 0;
        for (int lst = 0; lst <= 9; lst++)
            res = (res + dp[ID[{ lst, 0 }]][n]) % mod;
        return res;
    }
};

int main() {
    StringDecryption solver;
    cout << solver.decrypt({"23924"}) << endl;
}