#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int INF = 1e3 + 5;

struct rect {
    int x1, x2, y1, y2;
};

map<int, int> ID;

vector<rect> add[N], del[N];

int X[2][N], Y[2][N], Z[2][N];

int tag[N * 32], mn[N * 32], s[4][N * 32], ncnt;

void pushup(int rt) {
    mn[rt] = 1e9;
    for (int i = 0; i < 4; i++) mn[rt] = min(mn[rt], mn[s[i][rt]]);
    mn[rt] += tag[rt];
}

int X0, X1, Y0, Y1;

void push(int &rt, int lx, int rx, int ly, int ry, int x) {
    if (X1 < lx || X0 > rx || Y1 < ly || Y0 > ry) return;
    if (!rt) rt = ++ncnt;
    if (X0 <= lx && rx <= X1 && Y0 <= ly && ry <= Y1) {
        tag[rt] += x, mn[rt] += x;
        return;
    }
    int midX = (lx + rx) / 2;
    if (rx == lx + 1) midX = lx;
    int midY = (ly + ry) / 2;
    if (ry == ly + 1) midY = ly;
    if (X0 <= midX && Y0 <= midY) push(s[0][rt], lx, midX, ly, midY, x);
    if (X0 <= midX && Y1 > midY) push(s[1][rt], lx, midX, midY + 1, ry, x);
    if (X1 > midX && Y0 <= midY) push(s[2][rt], midX + 1, rx, ly, midY, x);
    if (X1 > midX && Y1 > midY) push(s[3][rt], midX + 1, rx, midY + 1, ry, x);
    pushup(rt);
}

int rt;

void FUCK(int a, int b, int c, int d, int x) {
    X0 = a, X1 = b, Y0 = c, Y1 = d;
    push(rt, -INF, INF, -INF, INF, x);
}

int px, py, flg;

void query(int rt, int lx, int rx, int ly, int ry, int x) {
    if (x + mn[rt] > 0) return;
    if (!rt) { flg = 1, px = lx, py = ly; return; }
    x += tag[rt];
    int midX = (lx + rx) / 2;
    if (rx == lx + 1) midX = lx;
    int midY = (ly + ry) / 2;
    if (ry == ly + 1) midY = ly;
    if (mn[s[0][rt]] + x <= 0) query(s[0][rt], lx, midX, ly, midY, x);
    else if (mn[s[1][rt]] + x <= 0) query(s[1][rt], lx, midX, midY + 1, ry, x);
    else if (mn[s[2][rt]] + x <= 0) query(s[2][rt], midX + 1, rx, ly, midY, x);
    else if (mn[s[3][rt]] + x <= 0) query(s[3][rt], midX + 1, rx, midY + 1, ry, x);
}

int get(int x) {
    static int id = 0;
    if (ID.count(x)) return ID[x];
    return ID[x] = ++id;
}

int main() {
    freopen("machine.in", "r", stdin), freopen("machine.out", "w", stdout);
    int n; scanf("%d", &n);
    vector<rect> base;
    vector<int> valX, valY, valZ;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d%d%d", &X[0][i], &X[1][i], &Y[0][i], &Y[1][i], &Z[0][i], &Z[1][i]);
        valX.push_back(X[0][i]), valX.push_back(X[1][i]);
        valY.push_back(Y[0][i]), valY.push_back(Y[1][i]);
        valZ.push_back(Z[0][i]), valZ.push_back(Z[1][i]);
        
    }
    sort(valX.begin(), valX.end());
    sort(valY.begin(), valY.end());
    sort(valZ.begin(), valZ.end());
    valX.resize(unique(valX.begin(), valX.end()) - valX.begin());
    valY.resize(unique(valY.begin(), valY.end()) - valY.begin());
    valZ.resize(unique(valZ.begin(), valZ.end()) - valZ.begin());

    auto find = [&](vector<int> &v, int x) {
        return lower_bound(v.begin(), v.end(), x) - v.begin();
    };

    for (int i = 1; i <= n; i++) {
        X[0][i] = find(valX, X[0][i]);
        X[1][i] = find(valX, X[1][i]);
        Y[0][i] = find(valY, Y[0][i]);
        Y[1][i] = find(valY, Y[1][i]);
        Z[0][i] = find(valZ, Z[0][i]);
        Z[1][i] = find(valZ, Z[1][i]);
        for (int t = 0; t <= 1; t++) {
            int w = t ? 1 : -1;
            Y[t][i] += w, Z[t][i] += w;
        }
        auto fuck = [&](vector<rect> &A, vector<rect> B) {
            for (auto t : B) A.push_back(t);
        };
        vector<rect> tmp;
        tmp.push_back({ -INF, Y[0][i], -INF, Z[0][i] });
        tmp.push_back({ -INF, Y[0][i], Z[1][i], INF });
        tmp.push_back({ Y[1][i], INF, -INF, Z[0][i] });
        tmp.push_back({ Y[1][i], INF, Z[1][i], INF });
        fuck(del[get(X[0][i])], tmp), fuck(add[get(X[1][i] + 1)], tmp);
        fuck(base, tmp);
    }
    for (auto t : base) FUCK(t.x1, t.x2, t.y1, t.y2, 1);
    for (auto t : ID) {
        int id = t.second;
        for (auto t : add[id]) FUCK(t.x1, t.x2, t.y1, t.y2, 1);
        for (auto t : del[id]) FUCK(t.x1, t.x2, t.y1, t.y2, -1);
        query(rt, -INF, INF, -INF, INF, 0);
        if (flg) {
            puts("YES");
            printf("%d %d %d\n", valX[t.first], valY[px], valZ[py]);
            return 0;
        }
    }
    puts("NO");
}