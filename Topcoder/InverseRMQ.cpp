#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

typedef pair<int, int> P;

struct edge {
    int to, w, next;
} e[N * 20];

int head[N], ecnt = 1;

void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, w, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, 0, head[to] }, head[to] = ecnt;
}

int dep[N];

bool BFS(int s, int t) {
    memset(dep, 0, sizeof(dep)), dep[s] = 1; 
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].next)
            if (e[i].w && !dep[e[i].to]) {
                dep[e[i].to] = dep[u] + 1, q.push(e[i].to);
                if (e[i].to == t) return true;
            }
    }
    return false;
}

int DFS(int u, int f, int t) {
    if (u == t || !f) return f;
    int res = 0;
    for (int i = head[u], tmp; i; i = e[i].next)
        if (e[i].w && dep[e[i].to] == dep[u] + 1 && (tmp = DFS(e[i].to, min(f, e[i].w), t))) {
            e[i].w -= tmp, e[i ^ 1].w += tmp, res += tmp, f -= tmp;
            if (!f) break;
        }
    return res;
}

int dinic(int s, int t) {
    int res = 0;
    while (BFS(s, t)) res += DFS(s, 1e9, t);
    return res;
}

int t = N - 10, ncnt = 0;

map<P, int> p;

void link(int s, int lst, int l, int r, int start, int end) {
    if (start > end) return;
    int rt;
    if (p.count(P(l, r))) rt = p[P(l, r)];
    else {
        rt = p[P(l, r)] = ++ncnt;
        if (lst) adde(lst, rt, 1e9);
    }
    if (start <= l && r <= end) return adde(s, rt, 1e9), void();
    int mid = (l + r) >> 1;
    if (start <= mid) link(s, rt, l, mid, start, end);
    if (end > mid) link(s, rt, mid + 1, r, start, end); 
}

int push(int l, int r) {
    if (!p.count(P(l, r))) return 0;
    int rt = p[P(l, r)];
    if (l == r) return adde(rt, t, 1), 1;
    int mid = (l + r) >> 1, sum = push(l, mid) + push(mid + 1, r);
    return adde(rt, t, r - l + 1 - sum), r - l + 1;
}

class InverseRMQ {
public:
    string possible(int n, vector<int> A, vector<int> B, vector<int> C) {
        int m = A.size();
        auto wkr = C; wkr.push_back(1), wkr.push_back(n);
        sort(wkr.begin(), wkr.end()), wkr.erase(unique(wkr.begin(), wkr.end()), wkr.end());
        int s = 1; ncnt = 1;
        vector<P> zzh;
        for (auto t : wkr) zzh.push_back(P(t, t));
        for (int i = 0; i + 1 < wkr.size(); i++) 
            if (wkr[i] + 1 < wkr[i + 1]) zzh.push_back(P(wkr[i] + 1, wkr[i + 1] - 1));
        // for (auto t : zzh) cout << "fuck: " << t.first << ' ' << t.second << endl;
        // for (auto tmp : zzh) assert(tmp.first <= tmp.second);
        for (auto tmp : zzh) { 
            int a = tmp.first, b = tmp.second, l = 1, r = n;
            for (int i = 0; i < m; i++) if (C[i] == b) 
                l = max(l, A[i]), r = min(r, B[i]);
            // if (b == 8) cout << l << ' ' << r << endl;
            int nw = ++ncnt;
            adde(s, nw, b - a + 1);
            vector<P> fuck;
            for (int j = 0; j < m; j++) if (b > C[j])
                fuck.push_back(P(A[j], B[j]));
            sort(fuck.begin(), fuck.end());
            // cout << a << ' ' << b << ' ' << l << ' ' << r << endl;
            int lst = l;
            for (int i = 0; i < fuck.size(); i++) {
                int j = i, r1 = fuck[i].second;
                while (j + 1 < fuck.size() && fuck[j + 1].first <= r1) j++, r1 = max(r1, fuck[j].second);
                if (lst <= fuck[i].first - 1) link(nw, 0, 1, n, lst, min(r, fuck[i].first - 1));
                i = j, lst = max(lst, r1 + 1);
            }
            link(nw, 0, 1, n, lst, r);
        }
        push(1, n);
        return dinic(s, t) == n ? "Possible" : "Impossible";
    }
};

// int main() {
//     scanf("%*d");
//     InverseRMQ solver;
//     vector<int> A, B, C;
//     int n, m; scanf("%d%d", &n, &m);
//     for (int i = 1, a, b, c; i <= m; i++) scanf("%d%d%d", &a, &b, &c), A.push_back(a), B.push_back(b), C.push_back(c);
//     cout << solver.possible(n, A, B, C) << endl;
// }