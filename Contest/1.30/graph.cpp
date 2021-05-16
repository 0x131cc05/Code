#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

typedef pair<int, int> P;

int ans[N], ct, from[N], to[N];

struct edge {
    int to, next, id;
} e[N * 2];

int head[N * 2], ecnt = 1, n, m;

void adde(int from, int to, int id) {
    e[++ecnt] = (edge){ to, head[from], id }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], id }, head[to] = ecnt;
}

int indA[N], indB[N], vis[N];

void dfs(int i, vector<int> &A, vector<int> &B) {
    if (vis[i >> 1]) return;
    vis[i >> 1] = 1;
    if (e[i].id) {
        if (e[i].to > n) A.push_back(e[i].id);
        else B.push_back(e[i].id);
    }
    for (int &j = head[e[i].to]; j; j = e[j].next)
        dfs(j, A, B);
}

void solve(vector<int> E, int mxD) {
    if (!E.size()) return;
    if (mxD == 1) {   
        ct++;
        for (int i = 0; i < E.size(); i++) ans[E[i]] = ct;
        return;
    }
    map<int, int> L, R; int A = 0, B = 0;
    for (int i = 0; i < E.size(); i++) {
        int t = E[i], u = from[t], v = to[t];
        if (!L.count(u)) L[u] = ++A;
        if (!R.count(v)) R[v] = ++B; 
        adde(L[u], n + R[v], t), indA[L[u]]++, indB[R[v]]++;
    }
    vector<int> L1, R1;
    for (int i = 1; i <= A; i++) if (indA[i] & 1) L1.push_back(i), indA[i] = 0;
    for (int i = 1; i <= B; i++) if (indB[i] & 1) R1.push_back(i), indB[i] = 0;
    while (L1.size() && R1.size()) 
        adde(L1.back(), n + R1.back(), 0), L1.pop_back(), R1.pop_back();
    while (L1.size()) {
        int a = L1.back(); L1.pop_back(); int b = L1.back(); L1.pop_back();
        B++, adde(a, n + B, 0), adde(b, n + B, 0);
    }
    while (R1.size()) {
        int a = R1.back(); R1.pop_back(); int b = R1.back(); R1.pop_back();
        A++, adde(A, n + a, 0), adde(A, n + b, 0);
    }
    for (int i = 2; i <= ecnt; i++) if (!vis[i >> 1]) dfs(i, L1, R1);
    for (int i = 1; i <= A; i++) head[i] = 0;
    for (int i = 1; i <= B; i++) head[i + n] = 0;
    for (int i = 1; i <= ecnt; i++) vis[i] = 0;
    E.resize(0), ecnt = 1, solve(L1, (mxD + 1) / 2), solve(R1, (mxD + 1) / 2);
}



int main() {
    freopen("graph.in", "r", stdin), freopen("graph.out", "w", stdout);
    int k; scanf("%d%d%d", &n, &m, &k); 
    vector<int> E;
    for (int i = 1; i <= k; i++) 
        scanf("%d%d", &from[i], &to[i]), E.push_back(i), indA[from[i]]++, indB[to[i]]++;
    int mx = 0;
    for (int i = 1; i <= n; i++) mx = max(mx, indA[i]), indA[i] = 0;
    for (int i = 1; i <= m; i++) mx = max(mx, indB[i]), indB[i] = 0;
    solve(E, mx);
    for (int i = 1; i <= k; i++) printf("%d\n", ans[i]);
}
