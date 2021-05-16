#include <bits/stdc++.h>
using namespace std;

const int N = 300010;

typedef long long LL;

vector<int> v[1000010];

int num[N], s[N], L[N], R[N], stk[N];

int get(int x, int l, int r) {
    return upper_bound(v[x].begin(), v[x].end(), r) - lower_bound(v[x].begin(), v[x].end(), l);
}

int main() {
    int n, k; scanf("%d%d", &n, &k);
    v[0].push_back(0);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &num[i]), s[i] = (s[i - 1] + num[i]) % k;
        v[s[i]].push_back(i);
    }
    int top = 1; stk[top] = 1;
    for (int i = 2; i <= n; i++) {
        while (top && num[stk[top]] < num[i]) R[stk[top--]] = i - 1;
        stk[++top] = i;
    }
    while (top) R[stk[top--]] = n;
    stk[top = 1] = n;
    for (int i = n - 1; i >= 1; i--) {
        while (top && num[stk[top]] <= num[i]) L[stk[top--]] = i + 1;
        stk[++top] = i;
    }
    while (top) L[stk[top--]] = 1;
    LL res = 0;
    for (int i = 1; i <= n; i++) {
        int l1 = L[i], r1 = i, l2 = i, r2 = R[i];
        if (r1 - l1 < r2 - l2) {
            for (int j = l1; j <= r1; j++) 
                res += get((s[j - 1] + num[i]) % k, l2, r2); 
        } else {
            for (int j = l2; j <= r2; j++) 
                res += get(((s[j] - num[i]) % k + k) % k, l1 - 1, r1 - 1);
        }
    }
    printf("%lld\n", res - n);
}