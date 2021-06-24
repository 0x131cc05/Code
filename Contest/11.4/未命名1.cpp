#include <bits/stdc++.h>
using namespace std;

const int N = 11;

int id[N], vis[N]; char s[N];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int k; scanf("%s%d", s + 1, &k);
        int l = strlen(s + 1);
        for (int i = 1; i <= l; i++) id[i] = i;
        int mx = 0, mn = 1e9;
        do {
            int ct = 0;
            for (int i = 1; i <= l; i++) vis[i] = 0;
            for (int i = 1; i <= l; i++) if (!vis[i]) {
                ct++; int t = i;
                while (!vis[t]) vis[t] = 1, t = id[t];
            }
            if (l - ct <= k && s[id[1]] != '0') {
                int res = 0;
                for (int i = 1; i <= l; i++) 
                    res = res * 10 + s[id[i]] - '0';
                mx = max(mx, res), mn = min(mn, res);
            }
        } while (next_permutation(id + 1, id + l + 1));
        printf("%d\n", mx - mn);
    }
}
