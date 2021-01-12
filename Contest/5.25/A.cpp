#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

typedef pair<int, int> P;

int num[N]; set<P> s1, s2; multiset<int> s, S1, S2;

LL res[N];

inline int calc(int pos) {
    return max(num[pos], num[pos + 1]) + min(num[pos], num[pos + 1]);
}

inline void del(int pos) {
    s2.erase(P(max(num[pos], num[pos + 1]), pos));
    s1.erase(P(min(num[pos], num[pos + 1]), pos));
}

int main() {
//    freopen("ex_data1.in", "r", stdin), freopen("out.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    for (int i = 1; i < n; i++) {
        int A = min(num[i], num[i + 1]), B = max(num[i], num[i + 1]);
        s2.insert(P(B, i)), s1.insert(P(A, i)), res[0] += B - A;
    }
    for (int i = 1, a; i <= m; i++) 
        scanf("%d", &a), s.insert(a);
    for (int i = 1; i <= m; i++) {
        int a = *s.begin(), b = *s.rbegin(), v[4];
        v[0] = S1.size() ? b + s1.rbegin() -> first - *S1.begin() : -1e9;
        v[1] = S2.size() ? -a - s2.begin() -> first + *S2.rbegin() : -1e9;
        v[2] = b - s2.begin() -> first;
        v[3] = s1.rbegin() -> first - a;
        int pos = 0;
        for (int i = 1; i < 4; i++) if (v[i] > v[pos]) pos = i;
        if (v[pos] < 0) {
            for (int j = i; j <= m; j++) res[j] = res[i - 1];
            break;
        }
        res[i] = res[i - 1] + v[pos] * 2;
        if (pos == 0) {
            int t = *S1.begin(); S1.erase(S1.begin()), S2.insert(t);
            s.erase(s.find(b)), S1.insert(calc(s1.rbegin() -> second)), del(s1.rbegin() -> second);
        } else if (pos == 1) {
            int t = *S2.rbegin(); S2.erase(S2.find(t)), S1.insert(t);
            s.erase(s.find(a)), S2.insert(calc(s2.begin() -> second)), del(s2.begin() -> second);
        } else if (pos == 2) {
            s.erase(s.find(b)), S2.insert(calc(s2.begin() -> second)), del(s2.begin() -> second);
        } else {
            s.erase(s.find(a)), S1.insert(calc(s1.rbegin() -> second)), del(s1.rbegin() -> second);
        }
    }
    for (int i = 1; i <= m; i++) printf("%lld ", res[i]);
} 
