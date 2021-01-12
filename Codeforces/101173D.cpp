#include <bits/stdc++.h>
using namespace std;

const int N = 7;

typedef pair<int, int> P;

int dp[N][N];

void DP() {
    dp[6][6] = dp[6][5] = dp[5][6] = 1;
    for (int i = 6; i >= 1; i--)
        for (int j = 6; j >= 1; j--) {
            if (dp[i][j]) {
                for (int k = i; k >= 1; k--)
                    for (int l = j; l >= 1; l--) {
                        if (k == i && l == j) continue;
                        dp[k][l] += dp[i][j];
                    }
            }
        }
}

void dfs(int x, int y, vector<int> v) {
    if (!v.size() || (x == 6 && y == 6)) return;
    reverse(v.begin(), v.end());
    if (x == 6 && y == 5) {
        if (v.size() == 1) puts("6 5 R 1");
        else puts(v[0] < v[1] ? "6 5 R 2" : "6 5 R 1\n6 5 R 1"); 
        return;
    } else if (x == 5 && y == 6) {
        if (v.size() == 1) puts("5 6 D 1");
        else puts(v[0] < v[1] ? "5 6 D 2" : "5 6 D 1\n5 6 D 1"); 
        return;
    }
    static P pos[40010]; int tot = v.size();
    for (int i = 6; i >= x; i--)
        for (int j = 6; j >= y; j--) {
            if (i == x && j == y) continue;
            int tmp = dp[i][j];
            while (tot && tmp--) pos[tot--] = P(i, j);
        }
    assert(!tot);
    int mn = *min_element(v.begin(), v.end());
    vector<int> push[7][7];
    for (auto t : v) {
        int tx = pos[t - mn + 1].first, ty = pos[t - mn + 1].second;
        // if (x == 4 && y == 5) cout << t << ' ' << tx << ' ' << ty << endl;
        for (int i = x; i < tx; i++) printf("%d %d D 1\n", i, y);
        for (int i = y; i < ty; i++) printf("%d %d R 1\n", tx, i);
        push[tx][ty].push_back(t);
    }
    for (int i = 6; i >= x; i--)
        for (int j = 6; j >= y; j--) 
            dfs(i, j, push[i][j]);
}

int main() {
    DP(); 
    int n; scanf("%d", &n);
    vector<int> plate;
    for (int i = 1, a; i <= n; i++) scanf("%d", &a), plate.push_back(a);
    dfs(1, 1, plate); 
}