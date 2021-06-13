#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

struct node { 
    int upMax, upMin, downMax, downMin, res; 
    int tagUp, tagDown;
} backup[N * 32], T[N << 2];

node merge(node a, node b) {
    return { max(a.upMax, b.upMax), min(a.upMin, b.upMin), max(a.downMax, b.downMax), min(a.downMin, b.downMin), max(a.res, b.res) };
}

int pos[N * 32], tail; 

void copy(int rt) {
    pos[++tail] = rt, backup[tail] = T[rt];
}

void pushup(int rt) {
    copy(rt), T[rt] = merge(T[rt << 1], T[rt << 1 | 1]);
}

void down1(int rt, int x) {
    copy(rt), T[rt].tagUp = x;
    T[rt].upMax = T[rt].upMin = x, T[rt].res = x - T[rt].downMin;
}

void down2(int rt, int x) {
    copy(rt), T[rt].tagDown = x;
    T[rt].downMax = T[rt].downMin = x, T[rt].res = T[rt].upMax - x;
}

void pushdown(int rt) {
    if (!T[rt].tagUp && !T[rt].tagDown) return;
    copy(rt);
    if (T[rt].tagUp) {
        down1(rt << 1, T[rt].tagUp), down1(rt << 1 | 1, T[rt].tagUp);
        T[rt].tagUp = 0;
    }
    if (T[rt].tagDown) {
        down2(rt << 1, T[rt].tagDown), down2(rt << 1 | 1, T[rt].tagDown);
        T[rt].tagDown = 0;
    }
}

void updateUp(int rt, int l, int r, int start, int end, int x) {
    if (start > end) return;
    if (T[rt].upMax <= x) return;
    if (start <= l && r <= end && x <= T[rt].upMin) 
        return down1(rt, x);
    pushdown(rt);
    int mid = (l + r) >> 1;
    if (start <= mid) updateUp(rt << 1, l, mid, start, end, x);
    if (end > mid) updateUp(rt << 1 | 1, mid + 1, r, start, end, x);
    pushup(rt);
}

void updateDown(int rt, int l, int r, int start, int end, int x) {
    if (start > end) return;
    if (T[rt].downMin >= x) return;
    if (start <= l && r <= end && x >= T[rt].downMax) 
        return down2(rt, x);
    pushdown(rt);
    int mid = (l + r) >> 1;
    if (start <= mid) updateDown(rt << 1, l, mid, start, end, x);
    if (end > mid) updateDown(rt << 1 | 1, mid + 1, r, start, end, x);
    pushup(rt);
}

vector<int> valX, valY, valZ;

void build(int rt, int l, int r) {
    T[rt].upMin = T[rt].upMax = valZ.size();
    T[rt].downMin = T[rt].downMax = 1, T[rt].res = (int)valZ.size() - 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
}

int cur;

void find(int rt, int l, int r) {
    if (T[rt].res < 0) return;
    if (l == r) {
        printf("YES\n%d %d %d\n", valX[cur - 1], valY[l - 1], valZ[T[rt].upMax - 1]);
        exit(0);
    }
    pushdown(rt);
    int mid = (l + r) >> 1;
    if (T[rt << 1].res >= 0) find(rt << 1, l, mid);
    else find(rt << 1 | 1, mid + 1, r);
}

struct rect {
    int x1, x2, y1, y2, z1, z2;
};

void back(int x) {
    while (tail > x) T[pos[tail]] = backup[tail], tail--;
}

int all;

void solve(int l, int r, vector<rect> &q) {
    if (T[1].res < 0) return;
    int lst = tail, mid = (l + r) >> 1;
    vector<rect> L, R;
    for (auto t : q) {
        if (t.x1 <= l && t.x2 >= r) {
            updateUp(1, 1, all, 1, t.y1 - 1, t.z2);
            updateUp(1, 1, all, t.y2 + 1, all, t.z2);
            updateDown(1, 1, all, 1, t.y1 - 1, t.z1);
            updateDown(1, 1, all, t.y2 + 1, all, t.z1);
        } else {
            if (t.x1 <= mid) L.push_back(t);
            if (t.x2 > mid) R.push_back(t);
        }
    }
    if (l == r) {
        if (T[1].res >= 0) cur = l, find(1, 1, all);
        return back(lst);
    }  
    solve(l, mid, L), solve(mid + 1, r, R), back(lst);
}

int main() {
    freopen("13.in", "r", stdin);
    // freopen("machine.out", "w", stdout);
    int n; scanf("%d", &n);
    vector<rect> base;
    for (int i = 1; i <= n; i++) {
        int x1, x2, y1, y2, z1, z2; scanf("%d%d%d%d%d%d", &x1, &x2, &y1, &y2, &z1, &z2);
        valX.push_back(x1), valX.push_back(x2);
        valY.push_back(y1), valY.push_back(y2);
        valZ.push_back(z1), valZ.push_back(z2);
        base.push_back({ x1, x2, y1, y2, z1, z2 });
    }
    auto reduce = [&](vector<int> &v) {
        sort(v.begin(), v.end()), v.resize(unique(v.begin(), v.end()) - v.begin());
    };
    reduce(valX), reduce(valY), reduce(valZ), all = valY.size();
    build(1, 1, valX.size());
    vector<rect> fuck;
    for (auto &t : base) {
        auto find = [&](vector<int> &v, int x) {
            return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
        };
        t.x1 = find(valX, t.x1) - 1, t.x2 = find(valX, t.x2) + 1;
        t.y1 = find(valY, t.y1), t.y2 = find(valY, t.y2);
        t.z1 = find(valZ, t.z1), t.z2 = find(valZ, t.z2);
        if (1 <= t.x1) fuck.push_back({ 1, t.x1, t.y1, t.y2, t.z1, t.z2 });
        if (t.x2 <= valX.size()) fuck.push_back({ t.x2, (int)valX.size(), t.y1, t.y2, t.z1, t.z2 });
    }
    solve(1, valX.size(), fuck), puts("NO");  
}