#include <bits/stdc++.h>
using namespace std;

const int N = 4010;

int len[N], id[N];
char s[N][N];

bool check(int a, int b) {
    if (len[a] > len[b]) return false;
    for (int i = 1, j = 1; i <= len[a]; i++) {
        while (j <= len[b] && s[b][j] != s[a][i]) j++;
        if (j > len[b]) return false;
        j++;
    }
    return true;
}

void fuck() {
    puts("impossible"), exit(0);
}

int main() {
    int n; scanf("%d", &n), n++;
    for (int i = 1; i <= n; i++) 
        scanf("%s", s[i] + 1), len[i] = strlen(s[i] + 1);
    for (int i = 1; i < n; i++) id[i] = i + 1;
    sort(id + 1, id + n, [](int a, int b) { return len[a] > len[b]; });
    vector<int> A, B, C;
    for (int i = 1; i < n; i++) {
        int t = id[i];
        bool a = A.size() ? check(t, A.back()) : 1;
        bool b = B.size() ? check(t, B.back()) : 1;
        if ((C.size() && check(t, C.back())) || (!C.size() && a && b)) C.push_back(t);
        else {
            if (a) {
                for (auto v : C) B.push_back(v);
                A.push_back(t), C.clear();
            } else if (b) {
                for (auto v : C) A.push_back(v);
                B.push_back(t), C.clear();
            } else fuck();
        }
    }
    for (auto t : C) A.push_back(t);
    if (A.size() && !check(A.back(), 1)) fuck();
    if (B.size() && !check(B.back(), 1)) fuck();
    printf("%d %d\n", A.size(), B.size()), reverse(A.begin(), A.end()), reverse(B.begin(), B.end());
    for (auto t : A) puts(s[t] + 1);
    for (auto t : B) puts(s[t] + 1);
}
