#include <bits/stdc++.h>
using namespace std;

char G[45][45];

struct status { 
    int x, y, d; 
    bool operator < (status b) const {
        if (x != b.x) return x < b.x;
        if (y != b.y) return y < b.y;
        return d < b.d;
    }
}; // n, s, e, w
int nxt[][2] = { { -1, 0 }, {1, 0}, {0, 1}, {0, -1} };
int lft[] = { 3, 2, 0, 1 }, trans[255]; char bk[] = { 'n', 's', 'e', 'w' };

bool check(status nw, char d) {
    if (d == 'b') return G[nw.x + nxt[nw.d][0]][nw.y + nxt[nw.d][1]] == '#';
    return trans[d] == nw.d;
}

string p[40]; vector<int> match[40];

void build(int nw) {
    match[nw].resize(p[nw].size());
    static int stk[110]; int top = 0;
    for (int i = 0; i < p[nw].size(); i++) {
        if (p[nw][i] == '(') stk[++top] = i;
        else if (p[nw][i] == ')') assert(top), match[nw][stk[top--]] = i;
    }
}

map<pair<status, status>, status> mp;

status process(status pos, status exec) {
    // cout << pos.x << ' ' << pos.y << ' ' << pos.d << ' ' << exec.d << ' ' << exec.x << ' ' << exec.y << endl; 
    if (pos.x == -1 || exec.x > exec.y) return pos;
    auto nw = make_pair(pos, exec);
    if (mp.count(nw)) return mp[nw];
    mp[nw] = { -1 };
    auto cur = pos;
    for (int i = exec.x; i <= exec.y && cur.x != -1; i++) {
        char c = p[exec.d][i];
        if (c == 'm') { if (!check(cur, 'b')) cur.x += nxt[cur.d][0], cur.y += nxt[cur.d][1]; }
        else if (c == 'l') cur.d = lft[cur.d];
        else if (c == 'i') {
            int l1 = i + 2, r1 = match[exec.d][l1], l2 = r1 + 1, r2 = match[exec.d][l2];
            if (check(cur, p[exec.d][i + 1])) cur = process(cur, { l1 + 1, r1 - 1, exec.d });
            else cur = process(cur, { l2 + 1, r2 - 1, exec.d });
            i = r2;
        } else if (c == 'u') {
            int l = i + 2, r = match[exec.d][l];
            if (!check(cur, p[exec.d][i + 1])) cur = process(process(cur, { l + 1, r - 1, exec.d }), { i, r, exec.d });
            i = r;
        } else {
            int jmp = p[exec.d][i] - 'A';
            cur = process(cur, { 0, (int)p[jmp].size() - 1, jmp });
        } 
    }
    return mp[nw] = cur;
}

int main() {
    trans['n'] = 0, trans['s'] = 1, trans['e'] = 2, trans['w'] = 3;
    for (int i = 0; i < 45; i++)
        for (int j = 0; j < 45; j++) G[i][j] = '#';
    int n, m, d, e; cin >> n >> m >> d >> e;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> G[i][j];
    for (int i = 1; i <= d; i++) {
        string tmp; cin >> tmp, p[tmp[0] - 'A'] = tmp.substr(2);
        build(tmp[0] - 'A');
    }
    for (int i = 1; i <= e; i++) {
        int x, y; char c; cin >> x >> y >> c;
        string tmp; cin >> tmp, p[i + 25] = tmp, build(i + 25);
        auto res = process({ x, y, trans[c] }, { 0, (int)tmp.size() - 1, i + 25 });
        if (res.x != -1) cout << res.x << ' ' << res.y << ' ' << bk[res.d] << endl;
        else cout << "inf" << endl;
    }
}