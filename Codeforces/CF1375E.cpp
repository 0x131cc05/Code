#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

int A[N], pos[N], buk[N];

int main() {
    int n; scanf("%d", &n); vector<int> v;
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]), v.push_back(A[i]);
    sort(v.begin(), v.end()), v.resize(unique(v.begin(), v.end()) - v.begin());
    for (int i = 1; i <= n; i++) {
        A[i] = lower_bound(v.begin(), v.end(), A[i]) - v.begin() + 1;
        buk[A[i]]++;
    }
    for (int i = 1; i <= n; i++) buk[i] += buk[i - 1];
    for (int i = n; i >= 1; i--) A[i] = buk[A[i]]--;
    vector<pair<int, int>> res;
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j++) pos[j] = 0;
        for (int j = 1; j < i; j++) if (A[j] > A[i]) 
            pos[A[j]] = j;
        int lst = A[i];
        for (int j = lst + 1; j <= n; j++) if (pos[j]) 
            swap(A[pos[j]], A[i]), res.push_back(make_pair(pos[j], i));
    }
    printf("%d\n", res.size());
    for (auto t : res) printf("%d %d\n", t.first, t.second);
}