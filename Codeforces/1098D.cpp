#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

typedef long long LL;

LL sum[32]; multiset<int> s[32];

int main() {
    int n, t = 0; scanf("%d", &n);
    while (n--) {
        char op[3]; int a; scanf("%s%d", op + 1, &a);
        int pos = 31 - __builtin_clz(a);
        if (op[1] == '+') 
            t++, s[pos].insert(a), sum[pos] += a;
        else t--, s[pos].erase(s[pos].find(a)), sum[pos] -= a;
        LL tp = 0; int res = 0;
        for (int i = 0; i <= 31; i++) if (sum[i]) {
            if (tp * 2 < *s[i].begin()) res++;
            tp += sum[i]; 
        }
        printf("%d\n", t - res);
    }
}
