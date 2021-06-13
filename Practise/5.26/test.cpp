#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 110;

LL dp[N][N]; int lst[N][N], fuck[] = {0, 1, 9, 9, 9, 9, 1};

int main() {
    int at = 1, k = 2;
    memset(dp, 0x3f, sizeof(dp)); 
    // dp[0][2] = 0;
    for (int i = 1; i <= 100; i++) dp[0][i] = -k;
    LL pw = 1;
    for (int i = 1; i <= 100; i++) {
        for (int j = 1; j <= 10; j++) if (dp[i - 1][j] < 1e17) {
            LL base = dp[i - 1][j];
            // int t = fuck[i];
            for (int t = at; t < 9; t++) {
                LL nxt = base;
                for (int l = 0; l < t; l++) {
                    nxt -= (j - (t == at) + (l == at) - k) * pw, nxt -= (i - 1) * pw / 10;
                }
                if (nxt < dp[i][j - (t == at)])
                    dp[i][j - (t == at)] = nxt, lst[i][j - (t == at)] = t;
            }
        }
        pw = pw * 10;
        if (dp[i][0] < 0 && i != 1) {
            cout << dp[i][0] << endl;
            for (int t = i, cur = 0; t >= 1; t--) {
                printf("%d", lst[t][cur]), cur += lst[t][cur] == at;
            }
            return 0;
        }
    }
}