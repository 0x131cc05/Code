#include <bits/stdc++.h>
using namespace std;

const int N = 5010;

int sg[N][N], k;

int SG(int n, int t) {
    if (sg[n][t] != -1) return sg[n][t];
    if (n == 0) return 0;
    vector<int> fuck;
    for (int i = 1; i <= t + k && i <= n; i++)
        fuck.push_back(SG(n - i, i));
    sort(fuck.begin(), fuck.end()), fuck.resize(unique(fuck.begin(), fuck.end()) - fuck.begin());
    for (int i = 0; i < fuck.size(); i++)
        if (fuck[i] != i) return sg[n][t] = i;
    return sg[n][t] = fuck.size();
}

int main() {
    memset(sg, -1, sizeof(sg));
    int l, r, res = 0; scanf("%d%d%d", &k, &l, &r), l--, r--;
    for (int i = l; i <= r; i++) cout << SG(i, 1) << ' ';
    printf("%d\n", res);
}
