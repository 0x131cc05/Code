#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

vector<int> A, B;

int U[N], M[N], D[N];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1, a; i <= m; i++) {
        scanf("%d", &a);
        if (a == 1) A.push_back(i);
        else B.push_back(i);        
    }
    if (A.size() + B.size() * 2 != 3 * n) return puts("no"), 0;
    int t = min(A.size(), B.size());
    for (int i = 1; i <= t; i++) 
        U[i] = A[i - 1], M[i] = D[i] = B[i - 1];
    if (t != n) {
        if (A.size() > B.size()) {
            int ct = t - 1;
            for (int i = t + 1; i <= n; i++)
                U[i] = A[++ct], M[i] = A[++ct], D[i] = A[++ct];
        } else {
            int ct = t - 1;
            for (int i = t + 1; i <= n; i += 2) {
                U[i] = M[i] = B[++ct], U[i + 1] = M[i + 1] = B[++ct];
                D[i] = D[i + 1] = B[++ct];
            }
        }
    }
    puts("yes");
    for (int i = 1; i <= n; i++) printf("%d ", U[i]);
    puts("");
    for (int i = 1; i <= n; i++) printf("%d ", M[i]);
    puts("");
    for (int i = 1; i <= n; i++) printf("%d ", D[i]);
}
