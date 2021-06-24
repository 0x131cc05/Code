#include <bits/stdc++.h>
using namespace std;

int v[27], lim, k;

vector<string> res;

void dfs(int cur) {
    cout << cur - 1 << ' ' << v[cur - 1] << endl;
    if (cur == lim) {
        if (v[cur - 1] == k) {
            cout << cur << endl;
//            cout << res.size() << endl;
//            for (auto t : res) cout << t << endl;
            exit(0);
        }
        return;
    }
    for (int i = 1; i < cur; i++) {
        for (int j = 1; j <= 3; j++) {
            v[cur] = v[i] << j;
            if (v[cur] > k) continue;
            dfs(cur + 1);
        } 
    }
    for (int i = 1; i < cur; i++)
        for (int j = 1; j < cur; j++) {
            for (int k = 0; k <= 3; k++) {
                v[cur] = v[i] + (v[j] << k);
                if (v[cur] > k) continue;
                dfs(cur + 1); 
            }
        }
}

int main() {
    cin >> k, v[1] = 1;
    for (int i = 4; i <= 4; i++) {
        cout << i << endl;
        lim = i, dfs(2);
    }
}