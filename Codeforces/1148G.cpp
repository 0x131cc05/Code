#include <bits/stdc++.h>
using namespace std;

const int M = 1e7 + 10;
const int N = 1e5 + 10;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int buk[M], mu[M], prime[M], tot, flag[M];

void sieve() {
    mu[1] = 1;
    for (int i = 2; i <= M - 10; i++) {
        if (!flag[i]) prime[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i * prime[j] <= M - 10; j++) {
            flag[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i]; 
        }
    }
}

vector<int> d[N];

void upd(int x, int y) {
    for (auto t : d[x]) buk[t] += y;
}

int que(int x) {
    int res = 0;
    for (auto t : d[x]) res += buk[t] * mu[t];
    return res;
}

int tmp[N], num[N], k, fuck[N];

vector<int> zero;

bool check() {
    if (zero.size() >= k) {
        for (int i = 0; i < k; i++) printf("%d ", zero[i]);
        exit(0);
    }
}

int main() {
    int n; scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &num[i]);
        for (int j = 1; j * j <= num[i]; j++) if (num[i] % j == 0) {
            d[i].push_back(j);
            if (j != num[i] / j) d[i].push_back(num[i] / j);
        }
    }
    sieve();
    for (int i = 1; i <= n; i++) upd(i, 1);
    int a = 0, b = 0, c = 0;
    for (int i = 1; i <= n; i++) {
        int wkr = que(i);
        if (wkr >= 2 && !a) {
            a = i;
            for (int j = 1; j <= n; j++) if (gcd(num[i], num[j]) == 1) {
                if (!b) b = j;
                else if (!c) c = j;
            }
        }
        if (wkr == 0) zero.push_back(i);
    }
    check();
    if (!a) {
        for (int i = 1; i <= n; i++) if (que(i) == 1) {
            zero.push_back(i), upd(i, -1);
            if (zero.size() == k) break;
        }
        for (auto t : zero) printf("%d ", t);
        return 0;
    }
    if (k <= 3) {
        printf("%d ", a);
        if (k >= 2) printf("%d ", b);
        if (k >= 3) printf("%d ", c);
        return 0;
    }
    zero.clear(), upd(a, -1), upd(b, -1), upd(c, -1); vector<int> remain;
    for (int i = 1; i <= n; i++) if (i != a && i != b && i != c) {
        if (que(i) == 0) zero.push_back(i);
        else remain.push_back(i);
    }
    check();
    int l = 0, r = remain.size() - 1, mid, pos = -1, del;
    auto process = [&](int mid) {
        memset(buk, 0, sizeof(buk));
        for (int i = 0; i <= mid; i++) upd(remain[i], 1);
    };
    while (l <= r) {
        mid = (l + r) >> 1, process(mid); 
        int ct = 0;
        for (int i = 0; i <= mid; i++) if (que(remain[i]) != 0) ct++;
        if (ct + 3 >= k) pos = mid, r = mid - 1, del = ct + 3 - k;
        else l = mid + 1;
    }
    assert(pos >= 0), process(pos);
    for (int i = 0, ls = -1; i < pos && del; i++) if (que(remain[i]) == 1 && gcd(num[remain[i]], num[remain[pos]]) == 1) {
        if (ls >= 0) del--, fuck[ls] = 1;
        ls = i;
    }
    for (int i = 0; i <= pos; i++) if (!fuck[i]) printf("%d ", remain[i]);
    printf("%d %d ", a, b);
    if (!del) printf("%d ", c);
} 