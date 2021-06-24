#include <bits/stdc++.h>
using namespace std;
 
using P = pair<int, int>;
 
template<class T> void read(T &x) {
    x = 0; char c = getchar(); bool flag = false;
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (flag) x = -x;
}
 
template<class T, typename... Tail> void read(T &x, Tail&... tail) {
   read(x), read(tail...);
}
 
const int N = 1000010;
 
int buk[N];
 
int main() {
    freopen("equal.in", "r", stdin), freopen("equal.out", "w", stdout);
    int n; read(n);
    for (int i = 1, a; i <= n; i++) 
        read(a), buk[a]++;
    vector<int> A, B; int tot = 0;
    for (int i = 1; i <= N - 10; i++) if (buk[i]) {
        bool flag = false;
        for (int j = i * 2; j <= N - 10; j += i) if (buk[j]) {
            flag = true; break;
        }
        if (flag) A.push_back(buk[i]);
        B.push_back(buk[i]), tot++;
    }
    sort(A.begin(), A.end()), sort(B.begin(), B.end());
    for (int i = 1; i < A.size(); i++) A[i] += A[i - 1];
    for (int i = 1; i < B.size(); i++) B[i] += B[i - 1];
    for (int i = 0; i <= n; i++) {
        int a = upper_bound(A.begin(), A.end(), i) - A.begin();
        int b = upper_bound(B.begin(), B.end(), i) - B.begin() - 1;
        printf("%d ", tot - max(a, b));
    }
    return 0;
}