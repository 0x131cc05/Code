#include <bits/stdc++.h>
using namespace std;

int val[2][10010];

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> val[0][i];
    for (int i = 1; i <= n; i++) cin >> val[1][i];
    for (int t = 1; t <= n * 3; t++) {
        for (int i = 1; i <= n; i++) {
            if (val[0][i] < val[1][i]) swap(val[0][i], val[1][i]);
        }
        int a = val[1][1]; val[1][1] = val[0][1];
        for (int i = 2; i <= n; i++)
            val[0][i - 1] = val[0][i];
        val[0][n] = a;
        for (int i = 1; i <= n; i++) {
            if (val[0][i] < val[1][i]) swap(val[0][i], val[1][i]);
        }
        for (int i = 1; i <= n; i++) printf("%d", val[0][i]);
        puts("");
        for (int i = 1; i <= n; i++) printf("%d", val[1][i]);
        puts("\n");
    }
}
