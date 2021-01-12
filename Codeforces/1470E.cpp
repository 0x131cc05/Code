#include <bits/stdc++.h>
using namespace std;

const int N = 30010;

typedef long long LL;

int num[N]; LL f[5][N], pre[5][N];

vector<int> pos[5][N];

void solve() {
    int n, c, q; cin >> n >> c >> q;
    for (int i = 1; i <= n; i++) cin >> num[i];
    for (int i = 0; i <= c; i++) f[i][n + 1] = 1, f[i][n + 2] = 0;
    for (int i = n; i >= 1; i--)
        for (int j = 0; j <= c; j++) {
            f[j][i] = 0;
            for (int k = 0; k <= j && i + k <= n; k++) 
                f[j][i] += f[j - k][i + k + 1];
        }
    for (int j = 0; j <= c; j++)
        for (int i = 1; i <= n; i++) {
            pos[j][i].clear();
            for (int k = 0; k <= j; k++) if (i + k <= n)
                pos[j][i].push_back(k);
            sort(pos[j][i].begin(), pos[j][i].end(), [&](int a, int b) { return num[i + a] < num[i + b]; });
            pre[j][i] = pre[j][i - 1];
            for (auto t : pos[j][i]) {
                if (!t) break;
                pre[j][i] += f[j - t][i + t + 1]; 
            }
        }
    while (q--) {
        LL id; int cur, p = 1, lst = c; cin >> cur >> id;
        if (id > f[c][1]) { cout << -1 << endl; continue; }
        while (233) {
            int l = p, r = n, mid, eql = p - 1;
            while (l <= r) {
                mid = (l + r) >> 1;
                LL tmp = pre[lst][mid] - pre[lst][p - 1];
                if (tmp < id && tmp + f[lst][mid + 1] >= id) eql = mid, l = mid + 1;
                else r = mid - 1;
            }
            id -= pre[lst][eql] - pre[lst][p - 1];
            if (p <= cur && cur <= eql) { cout << num[cur] << endl; break; }
            p = eql + 1; int len = 0;
            for (auto t : pos[lst][p]) {
                if (f[lst - t][p + t + 1] < id) id -= f[lst - t][p + t + 1];
                else { len = t; break; }
            }
            assert(len);
            if (p <= cur && cur <= p + len) { cout << num[p + len - cur + p] << endl; break; }
            p += len + 1, lst -= len;
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int T; cin >> T;
    while (T--) solve(); 
}