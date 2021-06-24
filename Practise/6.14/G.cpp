#include <bits/stdc++.h>
using namespace std;

const int N = 800010;

typedef long long LL;

int x[N], y[N], id[N];

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) 
        scanf("%d%d", &x[i], &y[i]), id[i] = i;
    sort(id + 1, id + n + 1, [&](int a, int b) {
        return x[a] + y[a] < x[b] + y[b];
    });
    LL cur = 0; multiset<LL> s, s1;
    LL l = 0, r = 1e9, tag = 0, b = 0;
    s.insert(l), s1.insert(r);
    for (int i = 1; i <= n; i++) {
        LL t = id[i], delta = x[t] + y[t] - cur;
        tag += delta, r += delta, cur += delta;
        LL pos = x[t];
        if (l <= pos && pos <= r) {
            l = r = pos, s.insert(pos), s1.insert(pos - tag);
        } else if (pos < l) {
            s.insert(pos), s.insert(pos);
            b += l - pos;
            s.erase(s.find(l)); LL t = *s.rbegin();
            s1.insert(l - tag), r = l, l = t;
        } else {
            s1.insert(pos - tag), s1.insert(pos - tag);
            b += pos - r;
            s1.erase(s1.find(r - tag)); LL t = *s1.begin() + tag;
            s.insert(r), l = r, r = t;
        }
    }
    printf("%lld\n", b);
}