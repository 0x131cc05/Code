#include <bits/stdc++.h>
using namespace std;

int num[1 << 19], tree[1 << 20], id[1 << 19], pos[1 << 19], n, k, m;

namespace sol1 {

struct WEN {

int x, y, id;

bool operator < (const WEN &b) {
    return x < b.x;
}

} q[200010];

int ans[200010], mx[19];

void main() {
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &q[i].x, &q[i].y), q[i].x--, q[i].id = i;
    sort(q + 1, q + m + 1);
    for (int i = 0, cur = 1; i < n; i++) {
        int pos = id[i];
        for (int j = 1; j <= k; j++) 
            mx[j] = max(mx[j], ++tree[pos >> j | (1 << k - j + 1)]);
        while (cur <= m && q[cur].x == i) {
            int t = q[cur].y, tp = -1;
            for (int j = 1; j <= k; j++) {
                int ct = 1 << j;
                if (!t && tree[pos >> j | (1 << k - j + 1)] != mx[j]) {
                    tp = j; break;
                }
                if (!((i + 1) >> j) || mx[j] < ct - t) {
                    tp = j; break;
                }
            }
            ans[q[cur].id] = tp == -1 ? k : tp - 1;
            cur++;
        }
        
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}

}

namespace sol2 {

inline int solve(int pos, int y) {
    int x = num[pos];
    for (int i = 1; i <= k; i++) {
        bool flag = false;
        if ((x + 1) >> i) for (int j = 0; j < n >> i && !flag; j++) {
            int l = j << i, r = ((j + 1) << i) - 1, ct = 0;
            for (int p = l; p <= r; p++) if (num[p] > x) ct++;
            if (y == 0) {
                if (l <= pos && pos <= r && !ct)
                    flag = true;
            } else if (ct <= y) flag = true;
        }
        if (!flag) return i - 1;
    }
    return k;
}

void main() {
    int last = 0;
    for (int i = 1; i <= m; i++) {
        int x, y; scanf("%d%d", &x, &y), x ^= last, y ^= last, x--;
        printf("%d\n", last = solve(pos[x], y));
    }
}

}

namespace sol3 {
    
void main() {
    for (int i = 1; i <= m; i++) {
        int x, y; scanf("%d%d", &x, &y);
        if (i != 1) printf("%d\n", y ^ 1);
        x ^= y ^ 1;
        if (i == m) printf("%d\n", sol2::solve(pos[x - 1], 1));
    }
}

}

int main() {
//    freopen("ex_arcahv3.in", "r", stdin), freopen("out.out", "w", stdout);
    int type; scanf("%d%d%d", &n, &k, &type);
    for (int i = 0; i < n; i++) scanf("%d", &num[i]), num[i]--, id[i] = i;
    for (int i = 0; i < n; i++) pos[num[i]] = i;
    sort(id, id + n, [](int a, int b) { return num[a] < num[b]; });
    scanf("%d", &m);
    if (type == 0) sol1::main();
    else if (n <= 256 || m <= 10) sol2::main();
    else sol3::main();
}
