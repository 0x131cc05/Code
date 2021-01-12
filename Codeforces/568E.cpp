#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

// l, p: 对于非空位置，以i结尾的最长上升子序列以及上一个位置
// f, g: 长度为i的上升子序列结尾的最小值以及位置
int l[N], p[N], f[N], g[N];

int num[N], use[N]; vector<int> remain;

int main() {
    int n, m; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    memset(f, 0x3f, sizeof(f)), memset(g, 0x3f, sizeof(g)), f[0] = g[0] = 0, scanf("%d", &m);
    for (int i = 1, a; i <= m; i++) 
        scanf("%d", &a), remain.push_back(a);
    sort(remain.begin(), remain.end());
    for (int i = 1; i <= n; i++) 
        if (num[i] != -1) {
            int l = 0, r = n, mid, pos = 0;
            while (l <= r) {
                mid = (l + r) >> 1;
                if (f[mid] < num[i]) pos = mid, l = mid + 1;
                else r = mid - 1;
            }
            ::l[i] = pos + 1, p[i] = g[pos];
            if (num[i] < f[pos + 1]) f[pos + 1] = num[i], g[pos + 1] = i;
        } else {
            int pos = 0; static int lst[N];
            for (int i = 0; i <= n; i++) lst[i] = f[i];
            for (auto a : remain) {
                while (lst[pos + 1] < a) pos++;
                if (a < f[pos + 1]) f[pos + 1] = a, g[pos + 1] = i;
            }
        }
    int ans = 0;
    while (g[ans + 1] <= n) ans++;
    int pos = g[ans], up = 1e9, t = remain.size() - 1;
    while (pos) {
        ans--;
        if (num[pos] == -1) {
            while (remain[t] >= up) t--;
            up = num[pos] = remain[t], use[t] = 1; bool flag = false;
            for (int i = 0; i < pos && !flag; i++) 
                if (l[i] == ans && num[i] != -1 && num[i] < up) 
                    pos = i, flag = true;
            if (!flag) while (num[pos] != -1) pos--;
        } else up = num[pos], pos = p[pos];
    }
    for (int i = 1; i <= n; i++) if (num[i] == -1)
        for (int j = 0; j < remain.size() && num[i] == -1; j++) if (!use[j])
            num[i] = remain[j], use[j] = 1;
    for (int i = 1; i <= n; i++) printf("%d ", num[i]);
    return 0;
}