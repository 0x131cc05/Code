#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef pair<int, int> P;

int f[N], g[N], dep[N];

vector<int> G[N];

void dfs1(int u, int fa) {
    vector<int> tmp; dep[u] = dep[fa] + 1;
    for (auto v : G[u]) if (v != fa) 
        dfs1(v, u), tmp.push_back(f[v]);
    f[u] = 1, sort(tmp.rbegin(), tmp.rend());
    for (int i = 0; i < tmp.size(); i++)
        f[u] = max(f[u], tmp[i] + i);
}

int ans;

void dfs2(int u, int fa, int val) {
    vector<P> tmp; int ct = 0;
    tmp.push_back(P(val, 0));
    for (auto v : G[u]) if (v != fa) 
        tmp.push_back(P(f[v], ++ct));
    sort(tmp.rbegin(), tmp.rend());
    vector<int> rnk(ct + 1), pre(ct + 1), suf(ct + 1);
    for (int i = 0; i < tmp.size(); i++)
        rnk[tmp[i].second] = i;
    g[u] = tmp[0].first; int delta = 0;
    for (int i = 1; i < tmp.size(); i++) 
        delta = max(delta, tmp[i].first + i - 1);
    g[u] += delta, ans = max(ans, g[u]); 
    for (int i = 0; i < tmp.size(); i++) {
        int hh = tmp[i].first + i;
        if (i) pre[i] = max(hh, pre[i - 1]);
        else pre[i] = hh;
    }
    for (int i = (int)tmp.size() - 1; i >= 0; i--) {
        int hh = tmp[i].first + i - 1;
        if (i + 1 != tmp.size()) suf[i] = max(suf[i + 1], hh);
        else suf[i] = hh;
    }
    ct = 0;
    for (auto v : G[u]) if (v != fa) {
        int id = rnk[++ct], w = max(id ? pre[id - 1] : 0, id + 1 == tmp.size() ? 0 : suf[id + 1]);
        dfs2(v, u, max(w, 1));
    }
}



int work(int u, int fa) {
    vector<int> tmp;
    for (auto v : G[u]) if (v != fa) 
        tmp.push_back(v);
    if (!tmp.size()) {
        cout << "? " << u << endl;
        int a; cin >> a;
        return a; 
    }
    sort(tmp.begin(), tmp.end(), [&](int a, int b) {
        return f[a] > f[b];
    });
    for (auto t : tmp) {
        int p = work(t, u);
        if (dep[p] != dep[u]) return p;
    }
    return u;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        G[a].push_back(b), G[b].push_back(a);
    }
    dfs1(1, 0), dfs2(1, 0, -1e9);
    cout << ans << endl;
    int rt; cin >> rt, dfs1(rt, 0);
    sort(G[rt].begin(), G[rt].end(), [&](int a, int b) {
        return f[a] > f[b];
    });
    int a = 0, b = 0;
    for (auto v : G[rt]) {
        int t = work(v, rt);
        if (t != rt) {
            if (a) { b = t; break; }
            else a = t;
        }
    }
    if (!b) b = rt;
    if (!a) a = rt;
    cout << "! " << a << ' ' << b << endl;
}


