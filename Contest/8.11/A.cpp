#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

typedef long long LL;

struct matrix {
    int a[29][29];
    matrix() { memset(a, 0, sizeof(a)); }
    int* operator [] (int x) { return a[x]; }
    matrix operator * (matrix &b) {
        matrix res;
        for (int i = 1; i <= 28; i++)
            for (int k = 1; k <= 28; k++) if (a[i][k])
                for (int j = 1; j <= 28; j++) 
                    res[i][j] = (res[i][j] + (LL)a[i][k] * b[k][j]) % mod;
        return res;
    }
};

matrix Pow(matrix x, LL y) {
    matrix res;
    for (int i = 1; i <= 28; i++) res[i][i] = 1;
    for (; y; y >>= 1, x = x * x) if (y & 1) res = res * x;
    return res;
}

int id[12][12]; matrix pw1[1 << 10], pw2[1 << 10], pw3[1 << 11];

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

vector<int> BM(vector<int> y) {
    vector<int> coef, diff; static int delta[210]; int fail = -1; 
    for (int i = 0, n = y.size(); i < n; i++) {
        delta[i] = y[i];
        for (int j = 0; j < coef.size(); j++) 
            delta[i] = (delta[i] - (LL)coef[j] * y[i - j - 1] % mod + mod) % mod;
        if (!delta[i]) continue;
        if (fail == -1) {
            fail = i, coef.resize(i + 1);
            continue;
        }
        int scale = (LL)delta[i] * Pow(delta[fail], mod - 2) % mod;
        vector<int> tmp = coef; coef.clear(), coef.resize(i - fail - 1), coef.push_back(scale);
        for (auto t : diff) coef.push_back((LL)t * (mod - scale) % mod);
        fail = i, diff = tmp;
        if (coef.size() < tmp.size()) coef.resize(tmp.size());
        for (int i = 0; i < tmp.size(); i++) coef[i] = (coef[i] + tmp[i]) % mod;
    }
    return coef;
}

int coef[] = {88, 999996370, 94002, 998293103, 23192616, 754748995, 72535962, 737503787, 35889529, 935120689, 35743270, 609772779, 461557012, 585685060, 665866766, 978058520, 2762720, 898093009, 327255944, 590939852, 126814461, 44977122, 377033101, 236375517, 347869477, 912733433, 692030831, 549056077};
int val[] = {1, 11, 120, 1372, 16151, 192489, 2296618, 27235034, 319587057, 701358826, 259450838, 539957899, 750222231, 926494110, 685164058, 775739884, 752265745, 559980468, 959990299, 504724428, 587461513, 404160978, 76071816, 579337256, 979436632, 596151047, 763290111, 300713329};

matrix FUCK(matrix a, matrix b) {
    matrix c;
    for (int i = 1; i <= 28; i++)
        for (int j = 1; j <= 28; j++)
            c[1][i] = (c[1][i] + (LL)a[1][j] * b[j][i]) % mod;
    return c;
        
}

int main() {
//    matrix base; 
//    for (int j = 0; j <= 9; j++)
//        for (int k = 1; j + k <= 10; k++) id[j][k] = ++tot;
//    tot++, base[tot][tot] = 1;
//    for (int j = 0; j <= 9; j++)
//        for (int k = 1; j + k <= 10; k++) {
//            int t = id[j][k];
//            base[t][id[j + k][1]] = j + k - 10 + mod;
//            base[t][id[j][k]] = k;
//            base[t][id[j][k + 1]] = 10 - j - k;
//            base[t][tot] = k;
//        }
//    vector<int> val;
//    for (int i = 1; i <= 28; i++) {
//        matrix nw = Pow(base, i);
//        cout << nw[id[0][1]][tot] << ", ";
//    }
//    auto res = BM(val);
//    for (auto t : res) cout << t << ", ";
    matrix base;
    for (int i = 1; i <= 28; i++) base[1][i] = coef[i - 1];
    for (int i = 2; i <= 28; i++) base[i][i - 1] = 1;
    for (int i = 1; i <= 28; i++) pw1[0][i][i] = pw2[0][i][i] = pw3[0][i][i] = 1;
    for (int i = 1; i < 1 << 10; i++) pw1[i] = pw1[i - 1] * base;
    matrix fuck = Pow(base, 1 << 10);
    for (int i = 1; i < 1 << 10; i++) pw2[i] = pw2[i - 1] * fuck;
    fuck = Pow(base, 1 << 20);
    for (int i = 1; i < 1 << 11; i++) pw3[i] = pw3[i - 1] * fuck;
    int T; scanf("%d", &T);
    int tmp = (1 << 10) - 1;
    while (T--) {
        LL n; scanf("%lld", &n);
        if (n <= 28) printf("%d\n", val[n - 1]);
        else {
            matrix res = FUCK(FUCK(pw3[(n - 28) >> 20], pw2[((n - 28) >> 10) & tmp]), pw1[(n - 28) & tmp]);
            int ans = 0;
            for (int j = 1; j <= 28; j++) 
                ans = (ans + (LL)res[1][j] * val[28 - j]) % mod;
            printf("%d\n", ans);
        }
    }
}
