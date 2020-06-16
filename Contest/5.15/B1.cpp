#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

vector<LL> pos; LL len, k; 

inline LL solve(LL r) {
    if (r < 0) return 0;
    if (r <= k) return 1;
    r -= k + 1; LL t = r / len;
    int t1 = upper_bound(pos.begin(), pos.end(), r % len) - pos.begin();
    return t * pos.size() + t1 + 1;
}

int main() {
    LL l, r; scanf("%lld%lld%lld", &k, &l, &r), k++;
    for (LL tp = 2; tp <= k; tp <<= 1) 
        pos.push_back(len), len += tp;
    pos.push_back(len), len += k + 1;
    LL up = 1;
    while (up < k) up <<= 1;
    LL lim = up - k;
    for (LL tp = 2; tp <= lim; tp <<= 1) 
        pos.push_back(len), len += tp;
    if (lim >= 1) pos.push_back(len), len += k + 1;
    printf("%lld\n", solve(r - 1) - solve(l - 2));
}
