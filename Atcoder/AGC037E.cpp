#include <bits/stdc++.h>
using namespace std;

const int N = 5010;

char s[N * 2]; int n;

inline void FUCK(char t) {
    for (int i = 1; i <= n; i++) putchar(t);
    exit(0);
}

int tmp[N * 2]; char res[N];

int main() {
    int k; scanf("%d%d%s", &n, &k, s + 1); char t = 127;
    for (int i = 1; i <= n; i++) t = min(t, s[i]);
    for (int i = n + 1; i <= n * 2; i++) s[i] = s[n * 2 - i + 1];
    for (int i = 1; i <= n; i++) res[i] = 127;
    if (k == 1) {
        for (int i = 1; i <= n + 1; i++) {
            bool flag = false;
            for (int j = 1; j <= n; j++) if (s[i + j - 1] != res[j]) {
                if (s[i + j - 1] < res[j]) flag = true;
                break; 
            } 
            if (flag) for (int j = 1; j <= n; j++) res[j] = s[i + j - 1];
        }
        for (int i = 1; i <= n; i++) putchar(res[i]); 
        return 0;
    }
    if (k >= 20) FUCK(t);
    int mx = 0;
    for (int i = 1; i <= n * 2; i++) if (s[i] == t) 
        tmp[i] = tmp[i - 1] + 1, mx = max(mx, tmp[i]);
    if ((mx << (k - 1)) >= n) FUCK(t);
    int all = mx << k - 1, len = n - mx;
    for (int i = 1; i <= all; i++) putchar(t);
    
    for (int i = 1; i <= n * 2; i++) if (tmp[i] == mx && i - mx - len + 1 >= 1) {
        int st = i - mx + 1; bool flag = false;
        for (int j = 1; j <= len; j++) if (s[st - j] != res[j]) {
            if (s[st - j] < res[j]) flag = true;
            break; 
        } 
        if (flag) for (int j = 1; j <= len; j++) res[j] = s[st - j];
    }
    for (int i = 1; i <= n - all; i++) putchar(res[i]);
}
