#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-12;

template<class T> void read(T &x) {
    x = 0; char c = getchar(); bool flag = false;
    while (!isdigit(c)) flag |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (flag) x = -x;
}

template<class T, typename... Tail> void read(T &x, Tail&... tail) {
   read(x), read(tail...);
}

double g[10010 * 25][75], p[4], v[10010 * 25]; char T[10010][25];
int nxt[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int n, m, L[10010 * 25];

int id(int i, int j) {
    return (i - 1) * m + j;
}

double& G(int i, int j) {
    assert(j >= L[i]);
    return g[i][j - L[i] + 1];
}

void Swap(int i, int j) {
    static double A[75], B[75]; 
    memcpy(A, g[i], sizeof(g[i])), memcpy(B, g[j], sizeof(g[j]));
    memset(g[i], 0, sizeof(g[i])), memset(g[j], 0, sizeof(g[j]));
    for (int t = i; t <= i + m * 2; t++) G(i, t) = B[t - L[j] + 1];
    for (int t = i; t <= i + m; t++) G(j, t) = A[t - L[i] + 1];
    swap(v[i], v[j]);
}

void gauss(int tot) {
    for (int i = 1; i <= tot; i++) {
        for (int j = i; j <= i + m; j++) if (fabs(G(i, j)) > eps) {
            Swap(i, j); break;
        }
        if (fabs(G(i, i)) < eps) continue;
        for (int j = i + 1; j <= i + m && j <= tot; j++) if (fabs(G(j, i)) > eps) {
            double t = G(j, i) / G(i, i);
            for (int k = i; k <= i + m * 2; k++) 
                G(j, k) -= G(i, k) * t;
            v[j] -= v[i] * t;
        }
    }
    for (int i = tot; i >= 1; i--) if (fabs(G(i, i)) > eps) {
        v[i] /= G(i, i);
        for (int j = max(1, i - m * 2); j < i; j++) 
            v[j] -= v[i] * G(j, i);
    }
}

int main() {
    read(m, n); double sum = 0;
    for (int i = 0; i < 4; i++) scanf("%lf", &p[i]), sum += p[i];
    for (int i = 0; i < 4; i++) p[i] /= sum;
    for (int i = 1; i <= n; i++) scanf("%s", T[i] + 1);
    int all = id(n, m);
    for (int i = 1; i <= all; i++) L[i] = max(1, i - m);
    int tot = 0;
    for (int i = 1; i <= m; i++) if (T[1][i] == '.') tot++;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) if (T[i][j] != 'X') {
            int u = id(i, j);
            for (int t = 0; t < 4; t++) {
                int tx = i + nxt[t][0], ty = j + nxt[t][1];
                if (T[tx][ty] != 'T') {
                    if (tx < 1 || ty < 1 || tx > n || ty > m || T[tx][ty] == 'X') {
                        if (T[i][j] != 'T') G(u, u) -= p[t];
                    } else G(u, id(tx, ty)) -= p[t ^ 1];
                }
            }
            G(u, u)++;
            if (i == 1) v[u] = 1. / tot;
        }
    gauss(all);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) if (T[i][j] == 'T') printf("%.10lf\n", v[id(i, j)]);
}