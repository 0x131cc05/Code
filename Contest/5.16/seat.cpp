#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, LL> P;

vector<P> A, B;

const int N = 100010; 

struct tcurts {
    LL pos; int id;
} q[N];

int ans[N], tp, Q, ta, tb;

inline void check(int x, LL t) {
    while (tp < Q && q[tp + 1].pos <= t) 
        tp++, ans[q[tp].id] = x;
}

void push(int a, LL b) {
    if (tb >= B.size()) return B.push_back(P(a, b)), void();
    if (B.back().first >= a) {
        if (B.back().first == a) B.back().second += b;
        else B.push_back(P(a, b));
    } else {
        P tmp = B.back();
        B.pop_back(), push(a, b), B.push_back(tmp);
    }
}

LL t;

inline void pushA() {
    check(A[ta].first, t += A[ta].second);
    int h1 = A[ta].first >> 1, h2 = A[ta].first - 1 - h1; LL c = A[ta].second; ta++; 
    if (h1 < h2) swap(h1, h2);
    if (h1) push(h1, c);
    if (h2) push(h2, c);
}

inline void pushB() {
    check(B[tb].first, t += B[tb].second);
    int h1 = B[tb].first >> 1, h2 = B[tb].first - 1 - h1; LL c = B[tb].second; tb++; 
    if (h1 < h2) swap(h1, h2);
    if (h1) push(h1, c);
    if (h2) push(h2, c);
};

bool cmp(tcurts a, tcurts b) {
    return a.pos < b.pos;
}

int main() {
    freopen("seat.in", "r", stdin), freopen("seat.out", "w", stdout);
    int n, x, _A, _B, _C, mod; scanf("%d%d%d%d%d%d", &n, &x, &_A, &_B, &_C, &mod);
    vector<int> tmp;
    for (int i = 1; i <= n; i++) 
        tmp.push_back(x), x = ((LL)_A * x % mod * x + (LL)_B * x + _C) % mod + 1;
    sort(tmp.begin(), tmp.end());
    for (int i = 0; i < tmp.size(); i++) {
        int j = i;
        while (j + 1 < tmp.size() && tmp[j + 1] == tmp[j]) j++;
        A.push_back(P(tmp[i], j - i + 1)), i = j;
    }
    reverse(A.begin(), A.end());
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) scanf("%lld", &q[i].pos), q[i].id = i;
    sort(q + 1, q + Q + 1, cmp); 
    while (ta < A.size() || tb < B.size()) {
        if (ta < A.size() && tb < B.size()) {
            if (A[ta].first >= B[tb].first) pushA();
            else pushB();
        } else {
            if (ta < A.size()) pushA();
            else pushB();
        }
    }
    for (int i = 1; i <= Q; i++) printf("%d\n", ans[i]);
}
