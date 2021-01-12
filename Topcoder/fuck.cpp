#include <bits/stdc++.h>
using namespace std;
 
int f[200][200][201][2];
 
class AlienAndPermutation {
 public:
  int getNumber(const std::vector<int> &P, int K) {
    if (K == 0) {
      return 1;
    }
    int n = static_cast<int>(P.size());
    std::vector<std::vector<bool>> tag(n, std::vector<bool>(n, true));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = std::min(i, j), stop = std::max(i, j); k <= stop; ++k) {
          if (P[k] > P[i]) {
            tag[i][j] = false;
            break;
          }
        }
      }
    }
    memset(f, -1, sizeof(f));
    return dfs(0, 0, K, 0, n, tag);
  }
 
 private:
  int dfs(int i, int j, int k, int t, int n,
          const std::vector<std::vector<bool>> &tag) {
    constexpr int kMod = 1000000007;
    if (k < 0) {
      return 0;
    }
    if (j == n) {
      return 1;
    }
    if (i == n) {
      return 0;
    }
    int &result = f[i][j][k][t];
    if (result != -1) {
      return result;
    }
    result = dfs(i + 1, j, k, 0, n, tag);
    if (tag[i][j]) {
      int new_k = k - ((i != j && t == 0) ? 1 : 0);
      int new_t = (t != 0 || i != j) ? 1 : 0;
      (result += dfs(i, j + 1, new_k, new_t, n, tag)) %= kMod;
    }
    return result;
  }
};

int main() {
    AlienAndPermutation solver;
    cout << solver.getNumber({8, 3, 1, 5, 10, 4, 7, 9, 6, 2},
3) << endl;
}