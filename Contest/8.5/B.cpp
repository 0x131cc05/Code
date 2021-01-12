#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int N = 5010;

typedef long long LL;
typedef pair<int, int> P;

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

int Pow(int x, int y, int mod = ::mod) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int phi, g;

int getg(int mod) {
    vector<int> num; int tmp = phi;
    for (int i = 2; i * i <= tmp; i++) if (tmp % i == 0) {
        num.push_back(i);
        while (tmp % i == 0) tmp /= i;
    }
    if (tmp != 1) num.push_back(tmp);
    for (int i = 2; i; i++) {
        bool flag = true;
        for (auto v : num) 
            if (Pow(i, phi / v, mod) == 1) { flag = false; break; }  
        if (flag) return i;
    }
}

int pw2[N], n;

vector<int> A, B;

int sol1() {
    int res = 0; sort(A.rbegin(), A.rend());
    for (int i = 0; i < A.size(); i++) {
        int ct = 1;
        for (int j = i + 1; j < A.size(); j++)
            if (A[i] % A[j] == 0) ct++;
        res = (res + pw2[n - ct]) % mod;
    }
    return res;
}

int ct[N]; map<int, int> mp;

int sol2(int mod) {
    for (int i = 0; i < B.size(); i++) mp[B[i]] = i;
    for (int i = 0; i < B.size(); i++) {
        int v = B[i];
        while (v) {
            if (mp.count(v)) ct[mp[v]]++;
            v = (LL)v * B[i] % mod;
        }
    }
    int res = 0;
    for (int i = 0; i < B.size(); i++)
        res = (res + pw2[n - ct[i]]) % ::mod;
    return res;
}

struct WEN {

static const int mod = 1000007;

vector<P> val[mod]; 

void insert(int x, int y) {
    int nw = x % mod;
    val[nw].push_back(P(x, y));
}

int qry(int x) {
    int nw = x % mod;
    for (auto v : val[nw])
        if (v.first == x) return v.second;
    return -1;
}

} s;

int ls, m;

int BSGS(int x, int mod) {
    for (int i = m, t = (LL)ls * Pow(x, phi - 1, mod) % mod; ; i += m, t = (LL)t * ls % mod) {
        int v = s.qry(t);
        if (~v) return i - v;
    }
    assert(0);
}

int num[N];

int main() {
    // freopen("game1.in", "r", stdin);
    int mod; scanf("%d%d", &n, &mod);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    phi = getphi(mod), g = getg(mod), pw2[0] = 1;
    for (int i = 1; i <= n; i++) pw2[i] = pw2[i - 1] * 2 % ::mod;
    m = ceil(sqrt(mod)), ls = 1;
    for (int i = 0; i < m; i++, ls = (LL)ls * g % mod) 
        s.insert(ls, i);
    for (int i = 1; i <= n; i++) {
        if (gcd(num[i], mod) == 1) A.push_back(gcd(BSGS(num[i], mod), phi));
        else B.push_back(num[i]);
    }
    printf("%d\n", (sol1() + sol2(mod)) % ::mod);
}