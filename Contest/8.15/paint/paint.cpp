#include "paint.h"

#include <vector>
#include <iostream>

using namespace std;

const int N = 100010;

int dp[N], ok[N], tag[N], lft[N], rgt[N]; 

int minimumInstructions(int n, int m, int k, vector<int> C, vector<int> A, vector<vector<int>> B) {
    vector<int> lst;
    for (int i = 1; i <= n; i++) lst.push_back(i);
    for (int i = 1; i <= m; i++) {
        for (auto t : B[i - 1]) tag[t] = i;
        vector<int> nw;
        for (auto t : lst) {
            if (t + i - 1 <= n && tag[C[t + i - 2]] == i) 
                nw.push_back(t), rgt[t] = i;  
        }
        lst = nw;
    }
    lst.clear();
    for (int i = 1; i <= n; i++) lst.push_back(i);
    for (int i = 0; i <= k; i++) tag[i] = 0;
    for (int i = m, l = 1; i >= 1; i--, l++) {
        for (auto t : B[i - 1]) tag[t] = i;
        vector<int> nw;
        for (auto t : lst) {
            if (t - l + 1 >= 1 && tag[C[t - l]] == i)
                nw.push_back(t), lft[t] = l;
        }
        lst = nw;
    }
    for (int i = 1; i <= n; i++) 
        for (int t = m - rgt[i]; t <= lft[i - 1]; t++) 
            ok[i - t] = 1;
    for (int i = 1; i <= n; i++) dp[i] = 1e9;
    dp[0] = 0;
    for (int i = 0, r = 0; i < n; i++) {
        if (ok[i + 1]) r = max(r, i + m);
        dp[r] = min(dp[r], dp[i] + 1);
    }
    return dp[n] < 1e7 ? dp[n] : -1;
}
