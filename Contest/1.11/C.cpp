#include <bits/stdc++.h>
using namespace std;

const int N = 600010;

typedef pair<int, int> P;

struct SA {
    int x[N], y[N], c[N], sa[N], rk[N], height[N], m, n;

    void sort() {
        for (int i = 1; i <= m; i++) c[i] = 0;
        for (int i = 1; i <= n; i++) c[x[i]]++;
        for (int i = 1; i <= m; i++) c[i] += c[i - 1];
        for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
    }

    void build(string s) { // s[0] = ' '
        n = (int)s.size() - 1, m = 127;
        for (int i = 1; i <= n; i++) 
            x[i] = s[i], y[i] = i;
        sort();
        for (int k = 1, num = 0; k <= n; k <<= 1) {
            for (int i = n; i >= n - k + 1; i--) y[++num] = i;
            for (int i = 1; i <= n; i++) if (sa[i] > k)
                y[++num] = sa[i] - k;
            sort(), memcpy(y, x, sizeof(x)), num = x[sa[1]] = 1;
            for (int i = 2; i <= n; i++) 
                x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? num : ++num;
            if (n == num) break;
            m = num, num = 0;
        }
    }

    void getHeight(string s) {
        for (int i = 1; i <= n; i++) rk[sa[i]] = i;
        for (int i = 1, k = 0; i <= n; i++) if (rk[i] != 1) {
            k = max(k - 1, 0);
            int lst = sa[rk[i] - 1];
            while (lst + k <= n && i + k <= n && s[lst + k] == s[i + k]) k++;
            height[rk[i]] = k;
        }
    }

    int mn[19][N], lg[N];

    void buildRMQ() {
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        for (int i = 2; i <= n; i++) mn[0][i] = height[i];
        for (int i = 1; i <= 18; i++)
            for (int j = 2; j + (1 << i) - 1 <= n; j++)
                mn[i][j] = min(mn[i - 1][j], mn[i - 1][j + (1 << i - 1)]);
    }

    int LCP(int a, int b) {
        if (a == b) return n;
        if (a > b) swap(a, b);
        int len = lg[b - a];
        return min(mn[len][a + 1], mn[len][b - (1 << len) + 1]);
    }
    
    P find(int pos, int x) {
        if (!x) return P(1, n);
        int l = 1, r = pos, mid, L = pos, R = pos;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (LCP(mid, pos) >= x) L = mid, r = mid - 1;
            else l = mid + 1;
        }
        l = pos, r = n;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (LCP(pos, mid) >= x) R = mid, l = mid + 1;
            else r = mid - 1;
        }
        return P(L, R);
    }

    void init(string s) { build(s), getHeight(s), buildRMQ(); }
} A, B;

struct Tree {
    int tree[N], n;
    void upd(int x) { for (; x <= n; x += x & -x) tree[x]++; }
    int que(int x) {
        int res = 0;
        for (; x; x -= x & -x) res += tree[x];
        return res;
    }
    int que(int l, int r) { return que(r) - que(l - 1); }
    void reset() { memset(tree, 0, sizeof(tree)); }
} T[27];

int pos[N], len[N], ans[N];

vector<P> fuck[N];

struct node {
    int l, r, id, w, c;
};

vector<node> wkr[N], zjk[N];

int main() {
//    freopen("pack4_10.in", "r", stdin), freopen("out.out", "w", stdout);
    ios::sync_with_stdio(false), cin.tie(0);
    int n, k, m; cin >> k;
    string all = " ", s;
    cin >> s >> m, all += s + '#', pos[0] = 1, n = s.size();
    for (int i = 1; i <= m; i++) 
        cin >> s, pos[i] = all.size(), all += s + '#', len[i] = s.size();
    A.init(all), reverse(all.begin() + 1, all.end()), B.init(all), reverse(all.begin() + 1, all.end());
    int tot = (int)all.size() - 1;
    for (int i = 1; i + k <= n; i++) {
        P at = P(max(1, B.rk[tot - (i - 1) + 1]), A.rk[i + k]);
        fuck[at.first].push_back(P(at.second, 26));
        fuck[at.first].push_back(P(at.second, all[i] - 'a'));
    }
    for (int i = 1; i <= m; i++) {
        if (len[i] <= k) { ans[i] = n - len[i] + 1; continue; }
        P tmp = B.find(B.rk[tot - (pos[i] + len[i] - 1) + 1], len[i]);
        zjk[n + 1].push_back({ tmp.first, tmp.second, i, 1, 26 });
        for (int j = 1; j <= len[i]; j++) {
            int nw = pos[i] + j - 1;
            P x = B.find(B.rk[tot - (nw - 1) + 1], j - 1), y(1, n);
            if (j + k <= len[i]) {
                y = A.find(A.rk[nw + k], len[i] - (j + k - 1));
                wkr[x.first - 1].push_back({ y.first, y.second, i, -1, 26 });
                wkr[x.second].push_back({ y.first, y.second, i, 1, 26 });
                wkr[x.first - 1].push_back({ y.first, y.second, i, 1, all[nw] - 'a' });
                wkr[x.second].push_back({ y.first, y.second, i, -1, all[nw] - 'a' });
            } else {
                int l = len[i] - j;
                zjk[n - l].push_back({ x.first, x.second, i, 1, 26 });
                zjk[n - l].push_back({ x.first, x.second, i, -1, all[nw] - 'a' });
            }
        }
    }
    for (int i = 0; i <= 26; i++) T[i].n = tot;
    for (int i = 1; i <= tot; i++) {
        for (auto t : fuck[i]) 
            T[t.second].upd(t.first);
        for (auto t : wkr[i]) ans[t.id] += T[t.c].que(t.l, t.r) * t.w;
    }
    for (int i = 0; i <= 26; i++) T[i].reset();
    for (int i = 2; i <= n + 1; i++) {
        int p = B.rk[tot - (i - 1) + 1];
        T[26].upd(p);
        if (i <= n) T[all[i] - 'a'].upd(p);
        for (auto t : zjk[i]) ans[t.id] += T[t.c].que(t.l, t.r) * t.w;
    }
    for (int i = 1; i <= m; i++) 
        printf("%d\n", ans[i]);
//        cout << ans[i] << endl;
} // FUCK THIS PROBLEM AND ITS AUTHOR
