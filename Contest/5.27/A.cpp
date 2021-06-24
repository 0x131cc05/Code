#include <bits/stdc++.h>
using namespace std;

bitset<70> base[70];

typedef long long LL;

int m;

inline void insert(bitset<70> s) {
    for (int i = m - 1; i >= 0; i--) if (s[i]) {
        if (base[i].any()) s ^= base[i];
        else { 
            for (int j = m - 1; j >= 0; j--) if (base[j][i]) 
                base[j] ^= s;
            base[i] = s;     
            return; 
        }
    }
} 

inline bool check(bitset<70> tmp, int cur) {
    for (int i = m - 1; i >= cur; i--) if (tmp[i]) {
        if (base[i].any()) tmp ^= base[i];
        else return false;
    }
    return true;
}

char s[200010][75]; int a[70], b[70], id[70];

LL pw3[36];

int main() {
//    freopen("ex_matrix1.in", "r", stdin);
    int n; scanf("%d%d", &n, &m), pw3[0] = 1;
    for (int i = 1; i <= 35; i++) pw3[i] = pw3[i - 1] * 3;
    for (int i = 1; i <= n; i++) 
        scanf("%s", s[i]); 
    for (int i = 0; i < m; i++) 
        scanf("%d%d", &a[i], &b[i]), id[i] = i;
    sort(id, id + m, [](int i, int j) {
        if (b[i] != b[j]) return b[i] < b[j];
        return a[i] < a[j];
    });
    for (int i = 1; i <= n; i++) {
        bitset<70> nw;
        for (int j = 0; j < m; j++) nw[j] = s[i][id[j]] == '1';
        insert(nw);
    }
    LL res = 0; bitset<70> ans;
    for (int i = m - 1; i >= 0; i--) {
        if (i && b[id[i]] == b[id[i - 1]]) {
            int mx = -2, ct = 0, ss = 0;
            for (int s = 0; s < 4; s++) {
                ans[i] = s & 1, ans[i - 1] = s >> 1;
                if (!check(ans, i - 1)) continue;
                if (ans[i] - ans[i - 1] == mx) ct++;
                else if (ans[i] - ans[i - 1] > mx) 
                    mx = ans[i] - ans[i - 1], ct = 1, ss = s;
            }
            if (ct == 1) ans[i] = ss & 1, ans[i - 1] = ss >> 1;
            else {
                auto tmp = base[i] ^ base[i - 1]; 
                for (int j = m - 1; j >= i - 1; j--) tmp[j] = 0;
                insert(tmp);
            }
        } else {
            if (a[id[i]] == 1) {
                ans[i] = 1;
                if (!check(ans, i)) ans[i] = 0;
            } else if (!check(ans, i)) ans[i] = 1;
        }
    }
    for (int i = m - 1; i >= 0; i--)
        res += ans[i] * a[id[i]] * pw3[b[id[i]]];
    printf("%lld\n", res);
}
