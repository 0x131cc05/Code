#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL, int> P;

#define fir first
#define sec second

const LL INF = 1e13;
const int N = 100010;

LL res; 

priority_queue<P> q0, q1;

void InsertA(int x) {
    P t = q1.top(); q1.pop();
    res += x - t.fir, q0.push(P(2 * x - t.fir, 0)); 
    if (t.sec) q1.push(t);
    while (true) {
        P t = q1.top(); 
        if (x - t.fir >= 0) break;
        q1.pop(), res += x - t.fir, q0.push(P(2 * x - t.fir, 0)), q1.push(P(x, 0));
        if (t.sec) q1.push(t); 
    }
    q0.push(P(x, 1));
}

void InsertB(int x) {
    P t = q0.top(); q0.pop();
    res += x - t.fir, q1.push(P(2 * x - t.fir, 0)); 
    if (t.sec) q0.push(t);
    while (true) {
        P t = q0.top(); 
        if (x - t.fir >= 0) break;
        q0.pop(), res += x - t.fir, q1.push(P(2 * x - t.fir, 0)), q0.push(P(x, 0));
        if (t.sec) q0.push(t); 
    }
    q1.push(P(x, 1));
}

int A[N], B[N];

int main() {
    int n, m; scanf("%d%d", &n, &m), q0.push(P(-INF, 1)), q1.push(P(-INF, 1));
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &B[i]);
    for (int i = 1, a = 1, b = 1; i <= n + m; i++) {
        if (a <= n && b <= m) {
            if (A[a] < B[b]) InsertA(A[a++]);
            else InsertB(B[b++]);
        } else if (a <= n) InsertA(A[a++]);
        else InsertB(B[b++]);
    }
    printf("%lld\n", res);
}
