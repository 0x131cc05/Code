#include <bits/stdc++.h>
using namespace std;

const int N = 3010;

int type[N], ct[3][N], col[N], m; 
vector<int> G[N];

char s[N];

void count(int u) {
    if (u <= m) return col[u] = s[u] - '0', void();
    for (auto v : G[u]) 
        count(v), ct[col[v]][u]++;
    if (!ct[0][u] && !ct[2][u]) col[u] = 1;
    else if (!ct[1][u] && !ct[2][u]) col[u] = 0;
    else col[u] = 2;
}

int ncnt;

void align(int u) {
    if (u <= m) return;
    if (ct[2][u] >= 2) puts("-1"), exit(0);
    if (type[u] == 0) { // P
        type[u] = 1;
        int P1 = ++ncnt, P2 = ++ncnt, P3 = 0;
        type[P1] = type[P2] = 0;
        vector<int> L, R;
        for (auto v : G[u]) {
            if (col[v] == 0) L.push_back(v);
            else if (col[v] == 1) R.push_back(v);
            else P3 = v;
        }
        G[u].clear();
        if (L.size()) G[u].push_back(P1), G[P1] = L;
        if (P3) G[u].push_back(P3);
        if (R.size()) G[u].push_back(P2), G[P2] = R;
        align(P3); 
    } else { // Q
        int nw = 0, tmp = 0;
        for (auto v : G[u]) {
            if (!col[v] && nw == 2) puts("-1"), exit(0);
            if (col[v]) nw = 1;
            else if (nw && !col[v]) nw = 2;
            if (col[v] == 2) tmp = v;
        }
        if (tmp) align(tmp);
    }
}

void reverse(int u) {
    
}
