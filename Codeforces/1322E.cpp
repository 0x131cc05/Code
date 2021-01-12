#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

int pre[N], n, mx;

inline void add(int l, int r, int x) {
    pre[l] += x, pre[r + 1] -= x;
}

inline void pushdown() {
    for (int i = 1; i <= n; i++) pre[i] += pre[i - 1];
}

int appear[N], len[N], num[N], val[N], tot;

// 维护极长的01交错序列

set<int> s; int st[N];

inline void down(int l, int r, int t) {
    int x = t - appear[l]; appear[l] = t; 
    if (st[l] == st[r]) {
        if (st[l] == 1) add(l, r, x);
    } else {
        if (st[l] == 1) add(l, l + (r - l + 1) / 2 - 1, x);
        else add(r - (r - l + 1) / 2 + 1, r, x);
    }
}

multiset<int> s1;

inline void M(int p, int l) {
    s1.erase(s1.find(len[p])), len[p] = l, s1.insert(l);
}

inline void erase(int p) {
    s.erase(p), s1.erase(s1.find(len[p]));
}

inline void insert(int p) {
    s.insert(p), s1.insert(len[p]);
}

inline void filp(int pos, int t) {
    int p = *--s.upper_bound(pos); 
    down(p, p + len[p] - 1, t);
    if (pos == p || pos == p + len[p] - 1) { 
        if (len[p] == 1) {
            int l = p == 1 ? p : *--s.upper_bound(pos - 1), tmp = 0;
            if (l != p) down(l, p - 1, t), erase(p), tmp++;
            if (p + 1 <= n) down(p + 1, p + len[p + 1], t), erase(p + 1), tmp += len[p + 1];
            M(l, len[l] + tmp);
        } else {
            if (pos == p) {
                if (pos == 1) len[2] = len[1] - 1, appear[2] = appear[1] = t, len[1] = 1, insert(2);
                else {
                    int l = *--s.find(p); down(l, l + len[l] - 1, t);
                    M(l, len[l] + 1), erase(p), len[p + 1] = len[p] - 1, appear[p + 1] = t, insert(p + 1);
                }
            } else {
                if (pos == n) len[n] = 1, M(p, len[p] - 1), appear[n] = t, insert(n);
                else {
                    int r = *++s.find(p); down(r, r + len[r] - 1, t);
                    M(p, len[p] - 1), len[pos] = len[r] + 1, appear[pos] = t, erase(r), insert(pos);
                }
            }
        }
    } else { 
        appear[pos] = appear[pos + 1] = t, len[pos] = 1, len[pos + 1] = p + len[p] - 1 - pos, M(p, pos - p);
        insert(pos), insert(pos + 1);
    }
    st[pos] ^= 1;
}

vector<int> pos[N];

int main() {
    scanf("%d", &n); 
    for (int i = 1; i <= n; i++) 
        scanf("%d", &num[i]), val[++tot] = num[i], len[i] = 1, s.insert(i), st[i] = 1, s1.insert(1);
    sort(val + 1, val + tot + 1), tot = unique(val + 1, val + tot + 1) - val - 1;
    for (int i = 1; i <= n; i++) {
        num[i] = lower_bound(val + 1, val + tot + 1, num[i]) - val;
        pos[num[i]].push_back(i);
    }
    for (int i = 1; i <= tot; i++) {
        for (auto t : pos[i]) filp(t, i);
        mx = max(mx, *s1.rbegin() - 1);
    }
    pushdown(), printf("%d\n", mx / 2); 
    for (int i = 1; i <= n; i++) printf("%d ", val[pre[i]]);
    return 0;
}