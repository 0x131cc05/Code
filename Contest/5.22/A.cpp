#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int M = 52;

typedef pair<int, int> P;
typedef long long LL;

struct WEN { P p; int id, type; };

#define x first
#define y second

vector<int> qL[M], qR[M];

P p[N], L[M], R[M]; int k;

inline void push(int id) {
    vector<WEN> tmp;
    for (int i = 1; i <= k; i++) if (L[i].y < p[id].y) {
        tmp.push_back((WEN){ L[i], i, 1 });
        tmp.push_back((WEN){ R[i], i, -1 });
    }
    sort(tmp.begin(), tmp.end(), [&](WEN a, WEN d) {
        P A = P(a.p.x - p[id].x, a.p.y - p[id].y), B = P(d.p.x - p[id].x, d.p.y - p[id].y);
        LL hh = (LL)A.x * B.y - (LL)A.y * B.x;
        if (hh != 0) return hh > 0;
        return a.type > d.type;
    });
//    for (int i = 0; i < tmp.size(); i++) cout << tmp[i].id << endl;
    for (int i = 0; i < tmp.size(); i++) {
        int j = i, sum = tmp[i].type;
        while (sum) j++, sum += tmp[j].type;
//        cout << "FUCK: " << id << ' ' << tmp[i].id << ' ' << tmp[j].id << endl;
        qL[tmp[i].id].push_back(id), qR[tmp[j].id].push_back(id), i = j;
    }
}

inline void check(int x) {
    auto Sort = [&](P t, vector<int> &tmp) {
        sort(tmp.begin(), tmp.end(), [&](int a, int b) {
            P A = P(p[a].x - t.x, p[a].y - t.y), B = P(p[b].x - t.x, p[b].y - t.y);
            return ((LL)A.x * B.y - (LL)A.y * B.x) > 0;
        });
    };
    Sort(L[x], qL[x]), Sort(R[x], qR[x]);
} 

int main() {
    int n, m, op; scanf("%d%d%d%d", &n, &k, &m, &op);
    for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y);
    for (int i = 1; i <= k; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        L[i].x = a, R[i].x = b, L[i].y = R[i].y = c;
    }
    for (int i = 1; i <= n; i++) push(i);
    for (int i = 1; i <= k; i++) check(i);
    int lastans = 0;
    while (m--) {
        P t; scanf("%d%d", &t.x, &t.y), t.x ^= lastans * op, t.y ^= lastans * op;
        int tot = 0;
        for (int i = 1; i <= k; i++) {
            P delta = P(L[i].x - t.x, L[i].y - t.y);
            int l = 0, r = qL[i].size() - 1, mid, ans = -1;
            while (l <= r) {
                mid = (l + r) >> 1; int pos = qL[i][mid];
//                cout << "check: " << pos << ' ' << l << ' ' << r << endl;
                if ((LL)(p[pos].x - L[i].x) * delta.y - (LL)(p[pos].y - L[i].y) * delta.x >= 0) ans = mid, l = mid + 1;
                else r = mid - 1;
            }
//            cout << "find: " << i << ' ' << ans << endl;
            tot += ans + 1, l = 0, r = qR[i].size() - 1, ans = -1;
            delta = P(R[i].x - t.x, R[i].y - t.y);
            while (l <= r) {
                mid = (l + r) >> 1; int pos = qR[i][mid];
                if ((LL)(p[pos].x - R[i].x) * delta.y - (LL)(p[pos].y - R[i].y) * delta.x > 0) ans = mid, l = mid + 1;
                else r = mid - 1;
            }
            tot -= ans + 1;
        }
        printf("%d\n", lastans = n - tot);
    }
}
