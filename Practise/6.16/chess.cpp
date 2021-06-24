#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> P;

vector<vector<P>> odd(int n, int offset = 0) {
    if (n == 1) return {};
    int step = n / 2;
    vector<vector<P>> res;
    for (int i = 1; i <= n; i++) {
        vector<P> tmp;
        int a = i, b = i == n ? 1 : i + 1;
        for (int j = 0; j < step; j++) {
            if (a + offset <= n && b + offset <= n) tmp.push_back(P(a + offset, b + offset));
            a--, b++;
            if (!a) a = n;
            if (b == n + 1) b = 1;
        }
        res.push_back(tmp);
    }
    return res;
}

vector<vector<P>> even(int n, int offset = 0) {
    int step = n / 2;
    vector<vector<P>> res;
    for (int len = 1; len < step; len++) {
        vector<P> A, B;
        for (int i = 1; i <= n; i++) {
            if (i & 1) A.push_back(P(i + offset, (i + len - 1) % n + 1 + offset));
            else B.push_back(P(i + offset, (i + len - 1) % n + 1 + offset));
        }
        res.push_back(A), res.push_back(B);
    }
    vector<P> lst;
    for (int i = 1; i <= step; i++) lst.push_back(P(i + offset, i + step + offset));
    res.push_back(lst);
    return res;
}

const int N = 1010;

int l[N];

void out(int x) {
    if (x >= 10) out(x / 10);
    putchar(x % 10 + '0');
}

int main() {
//    freopen("chess.in", "r", stdin), freopen("chess.out", "w", stdout);
    int n, k; scanf("%d%d", &n, &k);
    if (k == n / 2) {
        auto res = n & 1 ? odd(n) : even(n);
        out(res.size()), puts("");
        for (auto t : res) {
            out(t.size()), puts("");
            for (auto v : t) {
                out(v.first), putchar(' '), out(v.second), puts("");
            }
        }
    } else {
        vector<vector<P>> res;
        int B = n % (2 * k), A = n / (2 * k); // A - B 个 2k, B 个 2k + 1
        A = max(A, B); 
        int cur = 1;
        for (int i = 1; i <= A; i++) 
            l[i] = cur, cur += i <= B ? 2 * k + 1 : 2 * k;
        l[A + 1] = n + 1;
        for (int i = 1; i <= A; i++) {
            if (i <= B) {
                auto tmp = odd(2 * k + 1, l[i] - 1);
                for (auto t : tmp) res.push_back(t);
            } else {
                auto tmp = even(2 * k, l[i] - 1);
                for (auto t : tmp) res.push_back(t);
            }
        }
        auto case1 = [&](int a, int b, int len) {
            int r1 = a + k - 1, r2 = b + len - 1;
            for (int i = 0; i < len; i++) {
                vector<P> tmp;
                for (int j = a; j <= r1; j++) {
                    int t = j - a + b + i;
                    if (t > r2) t -= len;
                    if (j <= n && t <= n) tmp.push_back(P(j, t));
                }
                res.push_back(tmp);
            }
        };
        vector<P> fuck;
        auto case2 = [&](int a, int b, int id1, int id2) {
            int p1 = id2 % k + 1, p2 = id1 % k + 1;
            vector<int> A, B;
            A.push_back(p1 + a), B.push_back(p2 + b);
            for (int i = 0; i < k + 1; i++) 
                if (i != p1) A.push_back(a + i);
            for (int i = 0; i < k + 1; i++)
                if (i != p2) B.push_back(b + i);
            for (int i = 0; i < k + 1; i++) {
                vector<P> tmp;
                for (int j = 0; j < k + 1; j++) if (i != j) {
                    int t = (j + i) % (k + 1);
                    if (A[j] <= n && B[t] <= n)
                        tmp.push_back(P(A[j], B[t]));
                }
                res.push_back(tmp);
            }
            vector<P> tmp;
            for (int i = 1; i < k + 1; i++) {
                int j = i * 2 % (k + 1);
                if (A[i] <= n && B[j] <= n)
                    tmp.push_back(P(A[i], B[j]));
            }
            res.push_back(tmp);
            if (p1 + a <= n && p2 + b <= n) fuck.push_back(P(p1 + a, p2 + b));
        };
        for (int i = 1; i <= B; i++)
            for (int j = i + 1; j <= B; j++) {
                case1(l[i], l[j], k), case1(l[i], l[j] + k, k + 1), case1(l[j], l[i] + k, k + 1);
                case2(l[i] + k, l[j] + k, i, j);
            }
        for (int i = 1; i <= B; i++)
            for (int j = B + 1; j <= A; j++) {
                case1(l[i], l[j], k), case1(l[i], l[j] + k, k);
                case1(l[j], l[i] + k, k + 1), case1(l[j] + k, l[i] + k, k + 1);
            }
        for (int i = B + 1; i <= A; i++)
            for (int j = i + 1; j <= A; j++) {
                case1(l[i], l[j], k), case1(l[i], l[j] + k, k);
                case1(l[j], l[i] + k, k), case1(l[i] + k, l[j] + k, k);
            }
        for (int i = 0; i < fuck.size(); i++) {
            int j = min((int)fuck.size() - 1, i + k - 1);
            vector<P> tmp;
            for (int t = i; t <= j; t++) tmp.push_back(fuck[t]);
            res.push_back(tmp), i = j + 1;
        }
        vector<vector<P>> res1;
        for (auto t : res) {
            vector<P> tmp;
            for (auto v : t) {
                if (v.first <= n && v.second <= n) 
                    tmp.push_back(v);
            }
            if (tmp.size()) res1.push_back(tmp);
        }
        out(res1.size()), puts("");
        for (auto t : res1) {
            out(t.size()), puts("");
            for (auto v : t) {
                out(v.first), putchar(' '), out(v.second), puts("");
            }
        }
    }
}

