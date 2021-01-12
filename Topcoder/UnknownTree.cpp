#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 9;

#define pb push_back

typedef long long LL;
typedef pair<int, int> P;

void Inc(int &x, int y) { x += y, x -= x >= mod ? mod : 0; }

set<P> s;
int count(vector<int> A, vector<int> B, vector<int> C, int ab, int ac) {
    if (ac <= ab || ab <= 0) return 0;
    if (s.count(P(ab, ac))) return 0;
    s.insert(P(ab, ac));
    A.pb(0), B.pb(ab), C.pb(ac);
    A.pb(ab), B.pb(0), C.pb(ac - ab);
    A.pb(ac), B.pb(ac - ab), C.pb(0);
    int n = A.size(), res = 1;
    for (int i = 0; i < n; i++) {
        int ct = 0;
        for (int j = 0; j < n; j++)
            if (A[j] < A[i] && B[i] - A[i] == B[j] - A[j] && C[i] - A[i] == C[j] - A[j]) ct++;
        if (ct) { res = (LL)res * ct % mod; continue; }
        for (int j = 0; j < n; j++) if (i != j)
            if (A[j] == A[i] && B[i] - A[i] == B[j] - A[j] && C[i] - A[i] == C[j] - A[j]) return 0;
        if (A[i] <= ab && A[i] + B[i] == ab && A[i] + C[i] == ac) continue;
        if (A[i] > ab && A[i] - B[i] == ab && A[i] + C[i] == ac) continue;
        return 0;
    }
    return res;
}

int count(vector<int> A, vector<int> B, vector<int> C) {
    s.clear();
    int res = 0, a = 0, b = 0, c = 0, n = A.size();
    for (int i = 0; i < n; i++) {
        int ct = 0;
        for (int j = 0; j < n; j++) 
            if (A[j] < A[i] && B[i] - A[i] == B[j] - A[j] && C[i] - A[i] == C[j] - A[j]) ct++;
        if (!ct) { a = A[i], b = B[i], c = C[i]; break; }
    }
    auto fuck = [&](int ab, int ac) { Inc(res, count(A, B, C, ab, ac)); };
    fuck(a + b, a + c), fuck(b - a, c - a), fuck(a - b, a + c), fuck(a - b, a - c), fuck(a - b, c - b + a - b);
    return res;
}

struct UnknownTree {
    int getCount(vector<int> A, vector<int> B, vector<int> C) {
        int res = 0, n = A.size();
        Inc(res, count(A, B, C)), Inc(res, count(A, C, B)), Inc(res, count(B, A, C));
        for (int i = 0; i < n; i++) {
            int a = A[i], b = B[i], c = C[i];
            A.pb(0), B.pb(a + b), C.pb(a + c);
            A.pb(a + b), B.pb(0), C.pb(b + c);
            A.pb(a + c), B.pb(b + c), C.pb(0);
            int all = A.size(), nw = 1;
            for (int j = 0; j < all && nw; j++) if (j != i) {
                int ct = 0;
                for (int k = 0; k < all; k++) 
                    if (A[k] < A[j] && B[j] - A[j] == B[k] - A[k] && C[j] - A[j] == C[k] - A[k]) ct++;
                if (ct) { nw = (LL)nw * ct % mod; continue; }
                for (int k = 0; k < all; k++) if (j != k)
                    if (A[k] == A[j] && B[j] - A[j] == B[k] - A[k] && C[j] - A[j] == C[k] - A[k]) { nw = 0; break; }
                int delta = A[j] + B[j] + C[j] - a - b - c;
                if (A[j] <= a && B[j] == delta + b && delta == a - A[j]) continue;
                if (B[j] <= b && A[j] == delta + a && delta == b - B[j]) continue;
                if (C[j] <= c && A[j] == delta + a && delta == c - C[j]) continue;
                nw = 0;
            }
            A.resize(n), B.resize(n), C.resize(n), Inc(res, nw); 
        }
        return res;
    }
}; // FUCK THIS PROBLEM AND ITS AUTHOR

