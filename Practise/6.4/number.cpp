#include <bits/stdc++.h>
using namespace std;

bitset<30500> num;
bitset<15000> num1;

char s[200010];

int main() {
    freopen("number.in", "r", stdin), freopen("number.out", "w", stdout);
    scanf("%s", s + 1); int len = strlen(s + 1);
    for (int i = 0; i < len; i++) if (s[len - i] == '1') num[i] = 1;
    int res = 0, SZ = 300, cur = 0, tp = 0;
    while (233) {
        cur++;
        if (cur == SZ && tp == 0) {
            int len = 0; cur = 0;
            for (int i = 30000; i >= 0; i--) 
                if (num[i]) {
                    len = i; break;
                }
            if (len <= 14900) {
                for (int i = 0; i <= len; i++) num1[i] = num[i];
                tp = 1;
            }
        }
        if (!tp) {
            if (num.count() == 1 && num[0]) break;
            if (!num[0]) res++, num >>= 1;
            else {
                auto tmp = num << 1;
                while (tmp.any()) {
                    auto c = (tmp & num) << 1;
                    num ^= tmp, tmp = c;
                }
                int pos = 0;
                while (num[pos]) num[pos] = 0, pos++;
                num[pos] = 1, res++;
            }
        } else {
            if (num1.count() == 1 && num1[0]) break;
            if (!num1[0]) res++, num1 >>= 1;
            else {
                auto tmp = num1 << 1;
                while (tmp.any()) {
                    auto c = (tmp & num1) << 1;
                    num1 ^= tmp, tmp = c;
                }
                int pos = 0;
                while (num1[pos]) num1[pos] = 0, pos++;
                num1[pos] = 1, res++;
            }
        }
    }
    printf("%d\n", res);
}
