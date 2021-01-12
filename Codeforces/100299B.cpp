#include <bits/stdc++.h>
using namespace std;

const int N = 110;

typedef pair<int, int> P;

bool odd(vector<int> a) {
    int ct = 0;
    for (int i = 0; i < a.size(); i++)
        for (int j = i + 1; j < a.size(); j++) if (a[i] > a[j]) ct ^= 1;
    return ct;
}

int num[N][N], n, m, op[N][N];

int id(int i, int j) {
    return (i - 1) * m + j;   
}

vector<P> res;

void R(int t) {
    res.push_back(P(0, t));
    reverse(num[t] + 1, num[t] + m + 1);
    for (int i = 1; i <= m; i++) op[t][i] ^= 1;
}

void C(int t) {
    res.push_back(P(1, t));
    for (int i = 1; i <= n / 2; i++) swap(num[i][t], num[n - i + 1][t]);
    for (int i = 1; i <= n; i++) op[i][t] ^= 1; 
}

bool check(int i, int j) {
    return num[i][j] == id(i, j);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &m, &n), res.clear();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) scanf("%d", &num[i][j]);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if (id(i, j) != num[i][j] && id(i, m - j + 1) != num[i][j] &&
                    id(n - i + 1, j) != num[i][j] && id(n - i + 1, m - j + 1) != num[i][j]) goto fuck;
            } 
        for (int i = 1; i <= n / 2; i++)
            for (int j = 1; j <= m / 2; j++) op[i][j] = odd({ num[i][j], num[i][m - j + 1], num[n - i + 1][j], num[n - i + 1][m - j + 1] });
        for (int i = 1; i <= n / 2; i++) if (op[i][1]) R(i);
        for (int i = 1; i <= m / 2; i++) if (op[1][i]) C(i);
        for (int i = 1; i <= n / 2; i++)
            for (int j = 1; j <= m / 2; j++) if (op[i][j]) goto fuck;
        for (int i = 1; i <= n / 2; i++)
            for (int j = 1; j <= m / 2; j++) {
                int a = n - i + 1, b = m - j + 1;
                if (!check(i, j)) R(i), C(j), R(i), C(j);
                if (!check(i, j)) R(i), C(j), R(i), C(j);
                if (!check(i, j)) R(i), C(b), R(i), C(b);
                if (!check(a, b)) R(a), C(b), R(a), C(b);
                if (!check(a, b)) R(a), C(b), R(a), C(b);
            }
        if (n % 2 == 1 && !check(n / 2 + 1, 1)) R(n / 2 + 1);
        if (m % 2 == 1 && !check(1, m / 2 + 1)) C(m / 2 + 1);
        for (int i = 1; i <= n; i++) 
            for (int j = 1; j <= m; j++) if (!check(i, j)) goto fuck;
        printf("POSSIBLE %d ", res.size());
        for (auto t : res) printf("%c%d ", t.first ? 'C' : 'R', t.second);
        puts("");
        continue;
fuck:   puts("IMPOSSIBLE");
    }
}