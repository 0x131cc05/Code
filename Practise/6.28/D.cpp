#include <bits/stdc++.h>
using namespace std;

const int N = 8010;

char s[N];

int pos[N], pre[N], at[N], ban[N];
int dp[2][N], ct[N], wkr[N];

int main() {
    scanf("%s", s + 1); int n = strlen(s + 1);
    string A, B;
    ban[0] = 1;
    for (int i = 1, ct = 0, cur = 0; i <= n; i++) {
        pre[i] = pre[i - 1];
        if (s[i] == '(' || s[i] == ')') {
            if (s[i] == '(') {
                if (ct) ct--;
                else A += '(', cur++;
            } else {
                if (cur) cur--, A += ')';
                else ct++, A += "()";
            }
            wkr[B.size()] = i, B += s[i];
        } else pre[i]++, at[pre[i]] = i;
    }  
    int ans = 0;
    for (int i = 0, ctA = 0, ctB = 0; i < B.size(); i++) {
        if (A[i] == '(') ctA++; else ctB++;
        if (ctA == ctB) ban[i + 1] = 1;
        for (int j = 0, nw = 0; j < B.size(); j++) {
            if (B[j] == A[i]) nw++;
            if (nw == (A[i] == '(' ? ctA : ctB)) {
                pos[i] = j; break;
            }
        }
    }
    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < i; j++) if (pos[j] > pos[i]) ans++;
    memset(dp, 0x3f, sizeof(dp)), dp[0][0] = 0;
    int cur = 0;
    for (int i = 0; i <= A.size(); i++, cur ^= 1) {
        if (i) for (int j = 1; j <= n; j++) if (wkr[pos[i - 1]] < j)
            ct[j]++;
        memset(dp[cur ^ 1], 0x3f, sizeof(dp[cur ^ 1]));
        for (int j = 0; j <= pre[n]; j++) if (dp[cur][j] < 1e7) {
            if (i != A.size()) {
                int p = wkr[pos[i]], w = max(0, pre[p] - j);
                dp[cur ^ 1][j] = min(dp[cur ^ 1][j], dp[cur][j] + w);
            }
            if (j != pre[n]) {
                int p = at[j + 1];
                if (s[at[j + 1]] == 'x' && ban[i]) continue;
                int w = max(0, p - pre[p] - ct[p]);
                dp[cur][j + 1] = min(dp[cur][j + 1], dp[cur][j] + w);
            }
        }
    }
    printf("%d\n", dp[cur ^ 1][pre[n]] + ans);
}