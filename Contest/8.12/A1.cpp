#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int all;

void pushEdge(int u, int v) {
    printf("%d %d\n", all - v + 1, all - u + 1);
}

// 加入一个点: g' = f + g, f' = f
// 加入一条连向 n 的边: f' = f + g, g' = g 
// 初始状态 f = 1, g = 0
void generate(LL f, LL g, LL &n, LL &m, bool output = false) {
    if (!g) return n = 1, m = 0, void();
    if (f > g) {
        LL period = (f - 1) / g;
        generate(f - period * g, g, n, m, output), m += period;
        if (output) {
            for (int i = 1; i <= period; i++)
                pushEdge(n, 1);
        }
    } else {
        LL period = g / f;
        generate(f, g - period * f, n, m, output);
        if (output) {
            for (int i = 1; i <= period; i++)
                pushEdge(n + i - 1, n + i), pushEdge(n + i, n + i - 1);
        }
        n += period, m += period * 2;
    }
}

// 找一个与 c 互质的数，保证迭代到最后得到 f = 1, g = 0
LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

LL rnd() {
#if defined(__linux__)
    return rand() | ((LL)rand() << 32);
#else
    return rand() | (rand() << 16) | ((LL)rand() << 32) | ((LL)rand() << 48);
#endif
}

int main() {
    srand((LL)new char + time(0));
    LL c, l1, l2; cin >> c >> l1 >> l2;
    while (true) {
        LL g = rnd() % c + 1;
        while (gcd(g, c) != 1) g = rnd() % c + 1;
        LL n = 0, m = 0; generate(c, g, n, m);
        if (n <= l1 && m <= l2) {
            printf("%d %d\n", all = n, m), generate(c, g, n = 0, m = 0, true);
            return 0;
        }
    }
}