#include <bits/stdc++.h>
using namespace std;

const int N = 30010;
const int M = 1000010;

typedef pair<int, int> P;

struct edge {
    int to, next, w;
} e[M];

int head[N], ecnt = 1;

void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], 0 }, head[to] = ecnt;
}

int dep[N], cur[N];

bool BFS(int s, int t) {
    memset(dep, -1, sizeof(dep)), dep[s] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].next)
            if (e[i].w && dep[e[i].to] == -1) {
                dep[e[i].to] = dep[u] + 1;
                if (e[i].to == t) return true;
                q.push(e[i].to);
            }
    }
    return false;
}

int DFS(int u, int f, int t) {
    if (u == t || !f) return f;
    int res = 0, tmp;
    for (int &i = cur[u]; i; i = e[i].next)
        if (e[i].w && dep[e[i].to] == dep[u] + 1 && (tmp = DFS(e[i].to, min(f, e[i].w), t))) {
            res += tmp, f -= tmp, e[i].w -= tmp, e[i ^ 1].w += tmp;
            if (!f) break;
        }
    return res;
}

int dinic(int s, int t) {
    int res = 0;
    while (BFS(s, t)) memcpy(cur, head, sizeof(head)), res += DFS(s, 1e9, t);
    return res;
}

int idx[N], n;

void dfs(int u, int id, int t, vector<int> &v, int type = false) {
    if (u == t) return;
    if (u <= n) {
        v.push_back(u);
        if (type) idx[u] = id;
    }
    for (int i = head[u]; i; i = e[i].next)
        if (i % 2 == 0 && !e[i].w) { 
            dfs(e[i].to, id, t, v, type); break; 
        }
}

vector<int> p[4], q[3];

int fuck[3], vis[N], wkr[3];

map<P, int> col; set<P> E;

int main() {
//    freopen("A.in", "r", stdin), freopen("A.out", "w", stdout);
    int m; scanf("%d%d", &n, &m);
    int a, b, c; scanf("%d%d%d", &a, &b, &c);
    adde(a, a + n, 3);
    for (int i = 1; i <= n; i++) if (i != a) adde(i, i + n, 1);
    for (int i = 1, a, b; i <= m; i++) 
        scanf("%d%d", &a, &b), adde(a + n, b, 1), adde(b + n, a, 1), E.insert(P(a, b)), E.insert(P(b, a));
    int zzh = dinic(a, b);
    for (int i = head[a + n], ct = 0; i; i = e[i].next)
        if (i % 2 == 0 && !e[i].w) ct++, dfs(e[i].to, ct, b, p[ct], true);
    for (int i = 1; i <= n * 2; i++)
        for (int j = head[i]; j; j = e[j].next) {
            if (j % 2 == 0) e[j].w = 1;
            else e[j].w = 0;
            if (i == c && e[j].to == c + n) e[j].w = 2;
        }
    int t = n * 2 + 1;
    adde(a + n, t, 1), adde(b + n, t, 1);
    int res = dinic(c, t);
    if (res != 2) return puts("-1"), 0;
    for (int i = head[c + n], ct = 0; i; i = e[i].next) 
        if (i % 2 == 0 && !e[i].w) ct++, dfs(e[i].to, ct, t, q[ct]);
    for (int i = 1; i <= 3; i++) {
        auto fuck = [&](int u, int v) {
            col[P(u, v)] = col[P(v, u)] = i;
        };
        p[i].push_back(b);
        for (int j = 0; j < p[i].size(); j++) 
            fuck(j ? p[i][j - 1] : a, p[i][j]);
        p[i].pop_back();
    }
//    for (int i = 1; i <= 3; i++, puts(""))
//        for (auto t : p[i]) cout << t << ' ';
//    puts("--------------");
//    for (int i = 1; i <= 2; i++, puts(""))
//        for (auto t : q[i]) cout << t << ' ';
    for (int i = 1; i <= 2; i++) {
        for (auto t : q[i]) if (idx[t] && !fuck[i]) fuck[i] = t, wkr[i] = idx[t];
        if (!wkr[i]) {
            fuck[i] = c;
            for (int j = 0; j < q[i].size(); j++) {
                P tmp(j ? q[i][j - 1] : c, q[i][j]);
                if (col.count(tmp)) {
                    wkr[i] = col[tmp]; break;
                }
            }
        }
    }  
    q[1].pop_back(), q[2].pop_back();
    vector<int> ans;
    int ext = 0;
    for (int i = 1; i <= 3; i++) 
        if (i != wkr[1] && i != wkr[2]) { ext = i; break; }
    reverse(p[ext].begin(), p[ext].end());
    auto push = [&](int A, int B) {
        int u = fuck[A], v = fuck[B];
        ans.push_back(a);
        for (auto t : p[wkr[A]]) {
            if (t == c) break;
            ans.push_back(t);
            if (t == u) break;
        }
        vector<int> tmp;
//        cout << "fuck: " << u << ' ' << v << endl;
        for (auto t : q[A]) {
            if (t == u) break;
            tmp.push_back(t);
        }
        reverse(tmp.begin(), tmp.end());
        for (auto t : tmp) ans.push_back(t);
        ans.push_back(c), tmp.clear();
        for (auto t : q[B]) {
//            cout << "FUCK: " << t << ' ' << v << endl;
            if (t == v) break;
            ans.push_back(t);
        }
//        for (auto t : ans) cout << t << ' ';
//        cout << endl;
        bool flag = false;
        for (auto t : p[wkr[B]]) {
            flag |= t == v;
            if (t == c) continue;
            if (flag) ans.push_back(t);
        }
        ans.push_back(b);
        for (auto t : p[ext]) ans.push_back(t);
        ans.push_back(a);
    };
    push(1, 2);
    bool flag = true;
    for (int i = 1; i < ans.size(); i++) {
        if (!E.count(P(ans[i - 1], ans[i]))) {
            flag = false; break;
        }
        if (++vis[ans[i]] == 2) {
            flag = false; break;
        }
    }
    if (!flag) ans.clear(), push(2, 1);
    printf("%d\n", ans.size() - 1);
    for (auto t : ans) printf("%d ", t);
}
