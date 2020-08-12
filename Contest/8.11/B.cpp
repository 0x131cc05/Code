#include <bits/stdc++.h>
using namespace std;

const int N = 300010;

typedef pair<int, int> P;

vector<int> num[N];

char s[N];

void insert(set<int> &s, int x) {
    while (s.count(x)) s.erase(x), x++;
    s.insert(x);
}

bool cmp(set<int> &a, set<int> &b) {
    auto A = a.rbegin(), B = b.rbegin();
    while (233) {
        if (A == a.rend()) return true;
        if (B == b.rend()) return false;
        if (*A != *B) return *A < *B;
        A++, B++;
    }
}

set<int> solve(vector<int> &A, vector<int> &B) {
    int lim = max(A.size(), B.size()) - 1, mn = lim; bool flag = true;
    A.resize(lim + 1), B.resize(lim + 1);
    for (int i = lim; i >= 1; i--) {
        if (i + 1 > lim || (!A[i + 1] && !B[i + 1])) mn = min(mn, i);
        if (A[i] && B[i]) {
            flag = false; break;
        }
    }
    if (flag) mn = 0;
    set<int> s;
    for (int i = lim; i > mn; i--)
        if (A[i]) s.insert(i);
    if (!flag) s.insert(mn + 1);
    for (int i = 1; i <= lim; i++) if (B[i]) s.insert(i); 
    return s;
}

priority_queue<P> q;

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1); int l = strlen(s + 1);
        for (int j = 1; j <= l; j++) num[i].push_back(s[j] - '0');
        num[i].push_back(0);
        reverse(num[i].begin(), num[i].end());
        q.push(P(-l, i));
    }
    while (q.size() > 1) {
        int a = q.top().second; q.pop();
        int b = q.top().second; q.pop();
        int lim = max(num[a].size(), num[b].size()) - 1;
        set<int> tmpa = solve(num[a], num[b]), tmpb = solve(num[b], num[a]);
        if (cmp(tmpb, tmpa)) swap(tmpb, tmpa);
        lim++;
        if (!tmpa.count(lim)) lim--;
        cout << "merge: " << a << ' ' << b << endl;
//        for (auto t : num[a]) cout << t;
//        cout << endl;
//        for (auto t : num[b]) cout << t;
//        cout << endl;
        num[a].resize(lim + 1);
        for (int i = lim; i >= 1; i--)
            num[a][i] = tmpa.count(i), putchar(num[a][i] + '0');
        puts(""); 
        q.push(P(-num[a].size() + 1, a));
    }
    int a = q.top().second;
    for (int i = (int)num[a].size() - 1; i >= 1; i--) 
        putchar(num[a][i] + '0');
    
}
