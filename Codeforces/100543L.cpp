#include <bits/stdc++.h>
using namespace std;

template<class T> void read(T &x) {
    x = 0; char c = getchar(); bool flag = false;
    while (!isdigit(c)) flag |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (flag) x = -x;
}

template<class T, typename... Tail> void read(T &x, Tail&... tail) {
   read(x), read(tail...);
}

const int N = 610;

int L[N], R[N], h[N], dp[N][N];

int main() {
    int T; read(T);
    while (T--) {
        int n; read(n); 
        vector<int> tmp;
        for (int i = 1; i <= n; i++) read(L[i], R[i], h[i]), tmp.push_back(L[i]), tmp.push_back(R[i]);
        sort(tmp.begin(), tmp.end()), tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());
        for (int i = 1; i <= n; i++) {
            L[i] = lower_bound(tmp.begin(), tmp.end(), L[i]) - tmp.begin() + 1;
            R[i] = lower_bound(tmp.begin(), tmp.end(), R[i]) - tmp.begin() + 1;
        }
        int lim = tmp.size();
        for (int i = 1; i <= lim; i++) 
            for (int j = 1; j <= lim; j++)
                dp[i][j] = 1e9;
        for (int len = 1; len <= lim; len++)
            for (int l = 1; l + len - 1 <= lim; l++) {
                int r = l + len - 1, ct = 0, mx = 0;
                for (int i = 1; i <= n; i++) if (l <= L[i] && R[i] <= r) 
                    ct++, mx = max(mx, h[i]);
                if (ct == 0) { dp[l][r] = 0; continue; }
                for (int i = 1; i <= n; i++) if (l <= L[i] && R[i] <= r && mx == h[i]) {
                    for (int j = L[i]; j <= R[i]; j++) 
                        dp[l][r] = min(dp[l][r], dp[l][j - 1] + dp[j + 1][r] + h[i]);
                }
            }
        printf("%d\n", dp[1][lim]);
    }
}