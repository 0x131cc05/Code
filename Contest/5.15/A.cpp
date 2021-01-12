#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize(2)

const int N = 1000010;

template<class T> inline void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

struct tcurts {
    int x, y, id;
} p[N], p2[N];

int id1[N], id2[N], ct[N], ct1[N], rk[N], rk1[N]; char s[N];

int zjk[N], wkr[N];

namespace IO {
const int MAXSIZE = 1 << 20;
char buf[MAXSIZE], *p1, *p2;
#define gc()                                                               \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)
inline int rd() {
  int x = 0, f = 1;
  char c = gc();
  while (!isdigit(c)) {
    if (c == '-') f = -1;
    c = gc();
  }
  while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
  return x * f;
}
}

int main() {
    int n; scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++) p[i].x = IO::rd(), p[i].y = IO::rd(), p[i].id = i, p2[i] = p[i];
    for (int i = 1; i <= n; i++) id1[i] = id2[i] = i;
    sort(p + 1, p + n + 1, [](tcurts a, tcurts b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    sort(p2 + 1, p2 + n + 1, [](tcurts a, tcurts b) {
        return a.y == b.y ? a.x < b.x : a.y < b.y;
    });
    for (int i = 1; i <= n; i++)
        rk[p[i].id] = i, rk1[p2[i].id] = i;
    for (int i = 1; i <= n; i++) {
        ct[p[i].id] = 1;
        if (p[i].x == p[i - 1].x && p[i - 1].y == p[i].y - 1) ct[p[i].id] = ct[p[i - 1].id] + 1;
        ct1[p2[i].id] = 1;
        if (p2[i].y == p2[i - 1].y && p2[i - 1].x == p2[i].x - 1) ct1[p2[i].id] = ct1[p2[i - 1].id] + 1;
    }
    for (int i = 1; i <= n; i++) 
        zjk[i] = ct[p2[i].id], wkr[i] = ct1[p[i].id];
    int res = 0;
    for (int i = 1; i <= n; i++) {
        int l1 = min(ct[i], ct1[i] / 2), l2 = min(ct[i] / 2, ct1[i]); 
        for (int j = 1, A = rk[i], B = rk1[i] - 1; j <= l1; ++j, --A, B -= 2) if (s[j] == '1') 
            if (zjk[B] >= j && wkr[A] >= (j << 1)) res++;
        for (int j = 1, A = rk[i] - 1, B = rk1[i]; j <= l2; ++j, A -= 2, --B) if (s[j] == '1') 
            if (zjk[B] >= (j << 1) && wkr[A] >= j) res++;
    }
    printf("%d\n", res);
}
