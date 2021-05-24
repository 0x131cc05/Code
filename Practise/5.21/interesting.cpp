#include <bits/stdc++.h>
using namespace std;

const int N = 3010;

char G[N][N], G1[N][N];

int A[N], B[N], id1[N], id2[N];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%s", G[i] + 1);
    for (int i = 1; i <= n; i++) id1[i] = i;
    for (int i = 1; i <= m; i++) id2[i] = i;
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) if (G[i][j] == 'R') A[i]++, B[j]++;
    sort(id1 + 1, id1 + n + 1, [&](int a, int b) {
        return A[a] > A[b];
    });
    sort(id2 + 1, id2 + m + 1, [&](int a, int b) {
        return B[a] > B[b];
    });
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) G1[i][j] = G[id1[i]][id2[j]];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) if (G1[i][j] == 'R') {
            if (G1[i - 1][j] == 'B' || G1[i - 1][j - 1] == 'B' || G1[i][j - 1] == 'B') {
                puts("-1"); return 0;
            }
        }
    // for (int i = 1; i <= n; i++, puts(""))
    //     for (int j = 1; j <= m; j++) printf("%c", G1[i][j]);
    vector<int> lens;
    int lst = m;
    for (int i = 1; i <= n; i++) {
        lens.push_back(lst - A[id1[i]]), lst = A[id1[i]];
        int j = i;
        while (j < n && A[id1[i]] == A[id1[j + 1]]) j++;
        lens.push_back(j - i + 1), i = j;
    }
    lens.push_back(lst);
    int res = 0, mx = 0;
    for (auto t : lens) res += t, mx = max(mx, t);
    printf("%d\n", res - mx);
}