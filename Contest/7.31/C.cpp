#include <bits/stdc++.h>
using namespace std;

const int P = 331;
const int N = 200010;

typedef long long LL;

int inv[P], X[N], Y[N]; LL x; 
vector<int> wkr[P][P];

void chk(int a, int b) {
    if ((LL)X[a] * X[b] + (LL)Y[a] * Y[b] == x) 
        printf("%d %d\n", a, b), exit(0);
}

int main() {
//    freopen("T3.in", "r", stdin);
    int n; scanf("%d%lld", &n, &x);
    for (int i = 1; i < P; i++)
        for (int j = i + 1; j < P; j++) if (i * j % P == 1) {
            inv[i] = j, inv[j] = i; break;
        }
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &X[i], &Y[i]);
        wkr[X[i] % P][Y[i] % P].push_back(i);
    }
    int t = x % P;
    for (int a = 0; a < P; a++)
        for (int b = 0; b < P; b++) if (wkr[a][b].size()) {
            for (int c = 0; c < P; c++) {
                int r = t - a * c % P; r += (r >> 31) & P;
                if (!b) {
                    if (r) continue;
                    for (int d = 0; d < P; d++) {
                        for (auto u : wkr[c][d]) for (auto v : wkr[a][b]) 
                            chk(u, v);
                    }
                } else {
                    int d = r * inv[b] % P;
                    for (auto u : wkr[c][d]) for (auto v : wkr[a][b])
                        chk(u, v);
                }
            }
        }
}
