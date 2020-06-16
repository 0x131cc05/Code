#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

int num[N], mark[N], cnt[N]; LL ans[N];

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    for (int i = 1; i <= n / 2; i++) {
        int mx = -1e9, pos = 0, mx2 = -1e9, A = 0, B = 0;
        for (int j = 1; j <= n; j++) {
            if (!mark[j] && mx2 < mx + num[j]) 
                A = j, B = pos, mx2 = mx + num[j];
            if (!mark[j] && mx < -num[j]) pos = j, mx = -num[j]; 
        }
        int mx3 = -1e9, C = 0, D = 0;
        for (int j = 1; j < n; j++) if (cnt[j]) {
            int k = j;
            while (cnt[k]) k++;
            mx = -1e9, pos = 0;
            for (int l = k; l >= j; l--) {
                if ((!mark[l]) && mx3 < mx + num[l]) 
                    C = l, D = pos, mx3 = mx + num[l];
                if ((!mark[l]) && mx < -num[l]) pos = l, mx = -num[l];
            }
            j = k;
        }
        if (mx2 > mx3) {
            ans[i] = ans[i - 1] + max(mx2, 0), mark[A] = 1, mark[B] = 1;
            assert(B < A);
            for (int i = B; i < A; i++) cnt[i]++;
        } else {
            ans[i] = ans[i - 1] + max(mx3, 0), mark[C] = 1, mark[D] = 1;
            for (int i = C; i < D; i++) cnt[i]--;
        }
        printf("%lld ", ans[i]);
    }
}
