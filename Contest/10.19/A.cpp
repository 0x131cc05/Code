#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

template<class T> void read(T &x) {
    x = 0; char c = getchar(); bool flag = false;
    while (!isdigit(c)) c = getchar(), flag |= c == '-';
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (flag) x = -x;
}

template<class T, typename... Tail> void read(T &x, Tail&... tail) {
    read(x), read(tail...);
}

multiset<int> s[N];

int main() {
    int n, q; read(n, q);
    for (int i = 1; i <= n; i++) {
        int m, k; read(m, k), s[m].insert(k);
    }
    while (q--) {
        int op, a, b; read(op, a, b);
        if (op == 1) s[a].insert(b), n++;
        else {
            int lim = ceil(sqrt(b));
            for (int i = max(1, a - lim); i <= min(N - 10, a + lim); i++) {
                int remain = b - (a - i) * (a - i);
                while (s[i].size() && *s[i].begin() <= remain) 
                    n--, s[i].erase(s[i].begin());
            }
        }
        printf("%d\n", n);
    }
    return 0;
}