#include <bits/stdc++.h>
using namespace std;

const int N = 2010;

typedef long long LL;

int x[N], y[N], vis[N], n;

LL cross(int x1, int y1, int x2, int y2) {
    return (LL)x1 * y2 - (LL)y1 * x2;
}

int least1(int a, int b) {
    int pos = 0;
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        if (cross(x[b] - x[a], y[b] - y[a], x[i] - x[a], y[i] - y[a]) > 0) {
            if (!pos) pos = i;
            else if (cross(x[i] - x[b], y[i] - y[b], x[pos] - x[b], y[pos] - y[b]) > 0) pos = i;
        }
    }
    return pos;
} 

int least2(int a, int b) {
    int pos = 0;
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        if (cross(x[b] - x[a], y[b] - y[a], x[i] - x[a], y[i] - y[a]) < 0) {
            if (!pos) pos = i;
            else if (cross(x[i] - x[b], y[i] - y[b], x[pos] - x[b], y[pos] - y[b]) < 0) pos = i;
        }
    }
    return pos;
} 

int most1(int a, int b) {
    int pos = 0;
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        if (cross(x[b] - x[a], y[b] - y[a], x[i] - x[a], y[i] - y[a]) > 0) {
            if (!pos) pos = i;
            else if (cross(x[i] - x[b], y[i] - y[b], x[pos] - x[b], y[pos] - y[b]) < 0) pos = i;
        }
    }
    return pos;
}

int most2(int a, int b) {
    int pos = 0;
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        if (cross(x[b] - x[a], y[b] - y[a], x[i] - x[a], y[i] - y[a]) < 0) {
            if (!pos) pos = i;
            else if (cross(x[i] - x[b], y[i] - y[b], x[pos] - x[b], y[pos] - y[b]) > 0) pos = i;
        }
    }
    return pos;
}

char s[N];

void solve() {
    memset(vis, 0, sizeof(vis));
    vector<int> res;
    int lst = 1, st = 0;
    for (int i = 2; i <= n; i++) 
        if (y[i] < y[lst]) lst = i;
    vis[lst] = 1, res.push_back(lst);
    double mn = 1e9, mx = -1e9;
    for (int i = 1; i <= n; i++) if (i != lst) {
        double ang = atan2(y[i] - y[lst], x[i] - x[lst]);
        if (s[1] == 'L') {
            if (ang < mn) mn = ang, st = i;
        } else {
            if (ang > mx) mx = ang, st = i;
        }
    }
    vis[st] = 1, res.push_back(st);
    for (int t = 2; t < n; t++) {
        int tmp = st;
        if (s[t - 1] == s[t]) {
            if (s[t - 1] == 'L') st = least1(lst, st);
            else st = least2(lst, st);
        } else {
            if (s[t - 1] == 'L') st = most1(lst, st);
            else st = most2(lst, st);
        } 
        lst = tmp, vis[st] = 1, res.push_back(st);
    } 
    for (auto t : res) if (!t) return;
    for (auto t : res) printf("%d ", t);
    exit(0);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);
    scanf("%s", s + 1), solve();
    // puts("-1");
}