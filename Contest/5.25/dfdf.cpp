#include <bits/stdc++.h>
using namespace std;

const int N = 110;

int num[1010][N], n;

inline bool check(int t, int nw) {
    for (int i = 1; i <= n; i++)
        if (num[t][i] != num[nw][i]) return false;
    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &num[0][i]);
    for (int t = 1; t; t++) {
        for (int i = 1; i <= n; i++) num[t][i] = num[t - 1][i - 1] ^ num[t - 1][i + 1];
        for (int i = 1; i <= n; i++) if (num[t][i]) printf("%d ", num[t][i]);
        else printf("  ");
        puts("");
        for (int i = 0; i < t; i++) if (check(i, t)) {
            printf("period: %d", t - i);
            return 0;
        }
    }
} 
