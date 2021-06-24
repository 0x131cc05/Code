#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

const int N = 200010;

typedef pair<int, int> P;
typedef __int128 INT;

P p[N]; INT pre[N], pre1[N], prex[N], prey[N];

INT FUCK(P a, P b) {
    return (INT)a.x * b.y - (INT)a.y * b.x;
}

INT calc(int i, int l, int r, INT area) { // Fuck this problem and its author.
    INT A = pre1[r - 1] - pre1[l] - l * (pre[r - 1] - pre[l]);
    INT B = (prey[r - 1] - prey[l]) * p[i].x - (prex[r - 1] - prex[l]) * p[i].y;
    int ct = r - l - 1;
    INT tmp = A + B + FUCK(p[r], p[i]) * ct;
    if (tmp < 0) tmp = -tmp;
    return (tmp - area) * 2; // 0, 2, 4, ...
}

void print(INT x) {
    if (!x) return;
    print(x / 10), putchar('0' + x % 10);
}

int main() {
    freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
    int n; scanf("%d", &n);
    INT all = 0;
    for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y);
    for (int i = n + 1; i <= n * 2; i++) p[i] = p[i - n];
    for (int i = 1; i <= n * 2; i++) {
        INT tmp = FUCK(p[i], p[i + 1]);
        if (i <= n) all += tmp;
        pre[i] = tmp + pre[i - 1], pre1[i] = tmp * i + pre1[i - 1];
        prex[i] = p[i].x + prex[i - 1], prey[i] = p[i].y + prey[i - 1];
    }
    if (all < 0) all = -all;
    INT ans = 0;
    for (int i = 1; i <= n; i++) {
        int l = i + 2, r = i + n - 2, mid, pos; INT area;
        while (l <= r) {
            mid = (l + r) >> 1;
            INT zzh = pre[mid - 1] - pre[i - 1] + FUCK(p[mid], p[i]);
            if (zzh < 0) zzh = -zzh;
            if (zzh * 2 <= all) pos = mid, l = mid + 1, area = zzh;
            else r = mid - 1;
        }
        INT A = calc(i, i, pos, area), B = calc(i, pos - 1, i + n - 1, all - area); int ct = pos - i - 1;
        A = area * (n - 3 - ct) - area * ct + A, B = (all - area) * ct + (all - area) * (n - 3 - ct) - B;
        ans += A + B;
    }
    if (ans == 0) puts("0");
    else print(ans / 2);
}
