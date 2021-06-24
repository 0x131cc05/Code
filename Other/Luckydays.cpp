#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<unsigned int, int> P;

int mod;

const int SZ = 32768;

struct HashMap {
    vector<P> buff[SZ];

    void insert(unsigned int x, int y) {
        int t = x % SZ;
        buff[t].push_back(P(x, y));
    }

    int query(unsigned int x) {
        int t = x % SZ;
        for (auto v : buff[t]) if (v.first == x) return v.second;
        return -1;
    }

    void clear() {
        for (int i = 0; i < SZ; i++) buff[i].clear();
    }
} T1;

struct Matrix {
    int a[3][3];
    int* operator [] (int x) { return a[x]; }
    Matrix() { memset(a, 0, sizeof(a)); }

    Matrix operator * (Matrix &b) {
        Matrix res;
        for (int i = 0; i < 3; i++)
            for (int k = 0; k < 3; k++) if (a[i][k])
                for (int j = 0; j < 3; j++)
                    res[i][j] += a[i][k] * b[k][j];
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                res[i][j] %= mod;
        return res;
    }

    unsigned int get() {
        unsigned int res = 0;
        for (int i = 0; i < 3; i++) 
            for (int j = 0; j < 3; j++)
                res = res * 10007 + a[i][j];
        return res;
    }
} E;

int period(Matrix x) {
    HashMap mp;
    Matrix tmp = E;
    for (int i = 1; i <= mod; i++) 
        mp.insert(tmp.get(), i - 1), tmp = tmp * x;
    Matrix nw = tmp;
    for (int i = 1; i <= mod; i++) {
        int res = mp.query(nw.get());
        if (res != -1) return i * mod - res;
        nw = nw * tmp;
    }
    assert(0);
}

Matrix Pow(Matrix x, int y) {
    Matrix res = E;
    for (; y; y >>= 1, x = x * x) if (y & 1) res = res * x;
    return res;
}

void solveY0(int A, int B, int X, int Z, int C, int Q) {
//    cout << "FUCK" << endl;
    int p = 1, t = (B * X + Z) % mod;
    vector<int> wkr;
    if (t == C) wkr.push_back(1); 
    for (int i = 2, tA = t; ; i++) {
        tA = (tA * X + Z) % mod;
        if (tA == t) { p = i - 1; break; }
        if (tA == C) wkr.push_back(i);
    }
    auto calc = [&](LL r) {
        if (r <= 0) return 0ll;
        LL res = 0;
        if (A == C) res++;
        if (B == C && r >= 2) res++;
        if (r > 2) {
            res += wkr.size() * ((r - 2) / p);
            res += upper_bound(wkr.begin(), wkr.end(), (r - 2) % p) - wkr.begin();
        }
        return res;
    };
    while (Q--) {
        LL l, r; scanf("%lld%lld", &l, &r);
        printf("%lld\n", calc(r) - calc(l - 1));
    }
}

int main() {
//    freopen("in.in", "r", stdin), freopen("out.out", "w", stdout);
    int T; scanf("%d", &T), E[0][0] = E[1][1] = E[2][2] = 1;
    while (T--) {
        T1.clear();
        int A, B, X, Y, Z, C, Q; 
        scanf("%d%d%d%d%d%d%d%d", &A, &B, &X, &Y, &Z, &mod, &C, &Q);
        if (Y == 0) { solveY0(A, B, X, Z, C, Q); continue; }
        Matrix base, st;
        st[0][0] = B, st[0][1] = A, st[0][2] = 1;
        base[0][0] = X, base[1][0] = Y, base[2][0] = Z, base[0][1] = base[2][2] = 1;
        auto check = [&](int t) {
            Matrix zzh = Pow(base, t);
            Matrix tp = st * zzh;
            return tp.get() == st.get();  
        };
        int p = period(base), tp = p;
        for (int i = 1; i * i <= p; i++) if (p % i == 0) {
            if (check(i)) tp = min(tp, i);
            if (check(p / i)) tp = min(tp, p / i);
        }
//        Matrix zzh = Pow(base, tp);
//        for (int i = 0; i < 3; i++, puts(""))
//            for (int j = 0; j < 3; j++) cout << zzh[i][j] << ' ';
//        if (zzh.get() != E.get()) cout << "fuck" << endl;
//        cout << tp << endl;
        p = tp;
        int limA = pow(p, 0.25), limB = p / limA + 1;
        Matrix tmp = Pow(base, limA), nw = st * tmp;
        for (int i = 1; i <= limB; i++) 
            T1.insert(nw.get(), i * limA), nw = nw * tmp;
        vector<int> wkr;
        for (int i = 0; i < mod; i++) {
            Matrix t; t[0][0] = C, t[0][1] = i, t[0][2] = 1, t = t * base;
            for (int j = 1; j <= limA; j++) {
                int ans = T1.query(t.get());
                if (ans != -1) { wkr.push_back((ans - j + 1) % p + 1); break; }
                t = t * base;
            }
        }
        sort(wkr.begin(), wkr.end());
        auto calc = [&](LL r) {
            if (r <= 0) return 0ll;
            LL res = wkr.size() * (r / p);
            res += upper_bound(wkr.begin(), wkr.end(), r % p) - wkr.begin();
            return res;
        };
        while (Q--) {
            LL l, r; scanf("%lld%lld", &l, &r);
            printf("%lld\n", calc(r) - calc(l - 1));
        }
    }
}
