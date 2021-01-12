#include <bits/stdc++.h>
using namespace std;

const int N = 50010;

typedef pair<int, int> P;

#define fir first
#define sec second

priority_queue<int> s;

vector<P> wkr;

int A[N], B[N], n, m; 

bool check(int mid) {
    int cur = 0; vector<int> zjk; 
    while (s.size()) s.pop();
    for (int i = 1; i <= n; i++) {
        while (cur < wkr.size() && wkr[cur].fir <= A[i]) 
            s.push(wkr[cur].sec), cur++;
        for (int j = 1; j <= mid; j++) {
            if (!s.size()) break;
            s.pop();
        }
    }
    while (cur < wkr.size()) s.push(wkr[cur].sec), cur++;
    for (int i = m; i >= 1 && s.size(); i--) {
        if (s.size() > (long long)i * mid) return false;
        for (int j = 1; j <= mid && s.size(); j++) {
            if (s.top() > B[i]) return false;
            s.pop();
        }
    }
    return s.empty();
}

int main() {
    int t; scanf("%d%d%d", &n, &m, &t);
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]), A[i]--;
    for (int i = 1; i <= m; i++) scanf("%d", &B[i]), B[i]--;
    sort(A + 1, A + n + 1), sort(B + 1, B + m + 1);
    for (int i = 1; i <= t; i++) {
        int a, b; scanf("%d%d", &a, &b); wkr.push_back(P(a, b));
    }
    sort(wkr.begin(), wkr.end());
    int l = 1, r = t, mid, res = -1;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (check(mid)) r = mid - 1, res = mid;
        else l = mid + 1;
    }
    printf("%d\n", res);
}
