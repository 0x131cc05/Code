#include <cstdio>
#include <vector>
#include <algorithm>
 
const int N = 100 + 10;
 
int n, m, a[N][N];
 
std::vector< std::pair<char, int> > ans;
 
inline bool check(int x, int y) { return a[x][y] == (x - 1) * m + y; }
 
void row(int r) {
  ans.push_back(std::make_pair('R', r));
  std::reverse(a[r] + 1, a[r] + m + 1);
}
 
void col(int c) {
  ans.push_back(std::make_pair('C', c));
  for (int i = 1; i <= n - i; ++i) std::swap(a[i][c], a[n - i + 1][c]);
}
 
int main() {
  int tcase;
  for (scanf("%d", &tcase); tcase--;) {
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        scanf("%d", &a[i][j]);
    ans.clear();
    for (int i = 1; i <= n - i; ++i) {
      for (int j = 1; j <= m - j; ++j) {
        int x = n - i + 1, y = m - j + 1;
        if (!check(i, j)) row(i), col(y), row(i), col(y);
        if (!check(i, j)) row(i), col(y), row(i), col(y);
        if (!check(i, j)) row(x), col(j), row(x), col(j);
        if (!check(x, y)) row(x), col(y), row(x), col(y);
        if (!check(x, y)) row(x), col(y), row(x), col(y);
        if (!check(x, j)) {
//          if (i > 1) col(j), row(i), col(j); else 
          row(i), col(j), row(i);
        }
      }
    }
    if (n & 1) {
      int t = (n + 1) / 2;
      if (!check(t, 1)) row(t);
    }
    if (m & 1) {
      int t = (m + 1) / 2;
      if (!check(1, t)) col(t);
    }
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        if (!check(i, j)) goto fail;
    printf("POSSIBLE %d", ans.size());
    for (int i = 0; i < ans.size(); ++i) printf(" %c%d", ans[i].first, ans[i].second);
    putchar('\n');
    continue;
 fail:
    puts("IMPOSSIBLE");
  }
  return 0;
}
