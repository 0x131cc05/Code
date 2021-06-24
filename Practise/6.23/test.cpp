#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

typedef long long LL;

int phi;

int Pow(int x, int y, int mod = ::mod) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int getphi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            res = res / i * (i - 1);
        }
    if (n != 1) res = res / n * (n - 1);
    return res;
}

int getg(int mod) {
    vector<int> num; int tmp = phi;
    for (int i = 2; i * i <= tmp; i++) if (tmp % i == 0) {
        num.push_back(i);
        while (tmp % i == 0) tmp /= i;
    }
    if (tmp != 1) num.push_back(tmp);
    for (int i = 14; i; i++) {
        bool flag = true;
        for (auto v : num) 
            if (Pow(i, phi / v, mod) == 1) { flag = false; break; }  
        if (flag) return i;
    }
}

int main() {
    for (int i = 2; i < mod; i++) {
        if ((LL)i * i % mod * i % mod == 1) {
            cout << i << endl;
            break;
        }
    }
}
