#include <bits/stdc++.h>
using namespace std;

const int N = 5010;

int A[N], B[N]; char s[N];

inline void process(int t[], int n) {
    t[1] = s[1] == '1';
    for (int i = 2; i <= n; i++) t[i] = s[i] != s[i - 1];
}

int main() {
    int n; scanf("%d", &n);
    scanf("%s", s + 1), process(A, n), scanf("%s", s + 1), process(B, n);
    int ct = 0, ct1 = 0, res = 1e9;
    vector<int> wkr, zjk;
    for (int i = 1; i <= n; i++) {
        if (B[i]) wkr.push_back(i), ct1++;
        if (A[i]) zjk.push_back(i), ct++;
    }
    for (int t = -ct / 2 * 2; t <= ct1; t += 2) {
        int tp = 0, tmp = 0, tp1 = 0;
        for (int i = 1; i <= t; i++) tmp += wkr[tp++] - 1;
        for (int i = 1; i <= -t; i++) tmp += zjk[tp1++] - 1;
        for (int i = tp; i < wkr.size(); i++) {
            if (tp1 >= zjk.size()) tmp += n + 1 - wkr[tp++];
            else tmp += abs(wkr[tp++] - zjk[tp1++]);
        }
        for (int i = tp1; i < zjk.size(); i++) tmp += n + 1 - zjk[tp1++];
        res = min(res, tmp);
    }
    
    printf("%d\n", res);
}
