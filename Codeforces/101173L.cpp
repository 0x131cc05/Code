#include <bits/stdc++.h>
using namespace std;

const int N = 60;

int flip[N];

vector<array<int, 4>> res;

int a[3][N], hh[N], fuck[N];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < 3; i++) 
        for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
    int pos = -1;
    for (int i = 0; i < 3; i++) {
        bool flag = true;
        for (int j = 1; j <= n; j++) {
            int ct = 0;
            for (int k = 0; k < 3; k++) if (k != i) 
                ct += a[k][j] != a[i][j]; 
            if (ct == 2) {
                flag = false; break;
            }
        }
        if (flag) {
            pos = i; break;
        }
    }
    if (!~pos) return puts("-1"), 0;
    for (int i = 1; i <= n; i++) if (!a[pos][i]) 
        a[0][i] ^= 1, a[1][i] ^= 1, a[2][i] ^= 1, flip[i] = 1;
    auto push = [&](int a, int x, int b, int y) {
        res.push_back({ a, x ^ flip[a], b, y ^ flip[b] });
    };
    for (int i = 1; i <= n; i++) if (a[0][i] && a[1][i] && a[2][i]) 
        hh[i] = 1, push(i, 0, i, 1);
    int spec[3] = {0};
    for (int i = 1; i <= n; i++) if (!hh[i]) {
        int nw = 0;
        for (int j = 0; j < 3; j++) if (!a[j][i]) nw = j;
        fuck[i] = nw;
    }
    for (int i = 1; i <= n; i++) if (!hh[i]) {
        int nw = fuck[i];
        if (!spec[nw]) {
            spec[nw] = 1;
            for (int j = 1; j <= n; j++) if (j != i && !hh[j]) {
                push(i, 0, j, a[nw][j]);
                if (fuck[j] == nw) push(i, 1, j, 1);
            }
        }
    }
    printf("%d\n", res.size());
    for (auto t : res) {
        if (!t[1]) putchar('!');
        printf("x%d -> ", t[0]);
        if (!t[3]) putchar('!');
        printf("x%d\n", t[2]);
    }
}