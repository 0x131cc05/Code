#include <bits/stdc++.h>
using namespace std;

int num[11], mn[1 << 10];

int main() {
    int n; scanf("%d", &n);
    memset(mn, 0x3f, sizeof(mn));
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]), mn[1 << i - 1] = num[i];
    for (int s = 1; s < 1 << n; s++) {
        for (int ss = s; ; ss = (ss - 1) & s) {
            int sum = 0;
            for (int i = 1; i <= n; i++) {
                if (ss & (1 << i - 1)) 
                    sum -= num[i];
                else if (s & (1 << i - 1)) sum += num[i];
            }
            if (sum >= 0) mn[s] = min(mn[s], sum); 
            if (!ss) break;
        }
    }
    double ans = 1e9;
    for (int s = 1; s < 1 << n; s += 2) {
        for (int ss = s; ss; ss = (ss - 1) & s) {
            int t = ((1 << n) - 1) ^ s;
            if (!t || !(s ^ ss)) continue;
            int A = mn[ss], B = mn[s ^ ss], C = mn[((1 << n) - 1) ^ s];
            if (A > B) swap(A, B);
            if (B > C) swap(B, C);
            if (A + B < C) continue;
            double p = (A + B + C) / 2.;
            ans = min(ans, sqrt(p * (p - A) * (p - B) * (p - C)));
        }
    }
    printf("%.10lf\n", ans);
}
