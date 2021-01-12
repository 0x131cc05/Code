#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef long long LL;

typedef pair<LL, int> P;

multiset<P> S1, S2, S3, S4, S5, S6;

// S4: 所有只取了两个的堆; S5: 所有取了 >= 3 个的堆的堆顶 

vector<int> num[N]; int pos[N];

inline void insert(int x) {
    if (pos[x] == 2 && 2 < num[x].size()) S1.erase(P(num[x][2], x)), S4.erase(P(num[x][0] + num[x][1], x));
    S2.insert(P(num[x][0] + num[x][1], x));
    if (num[x].size() >= 3) S3.insert(P((LL)num[x][0] + num[x][1] + num[x][2], x));
    pos[x] = 0;
}

inline void erase(int x) {
    S2.erase(S2.find(P(num[x][0] + num[x][1], x))), S4.insert(P(num[x][0] + num[x][1], x));
    if (num[x].size() >= 3) {
        S3.erase(S3.find(P((LL)num[x][0] + num[x][1] + num[x][2], x)));
        S1.insert(P(num[x][2], x));
    }
    pos[x] = 2;
}

inline void up(int x) {
    if (pos[x] == 2) S4.erase(S4.find(P(num[x][0] + num[x][1], x))), S6.insert(P((LL)num[x][0] + num[x][1] + num[x][2], x));
    else if (pos[x] == 3) S6.erase(S6.find(P((LL)num[x][0] + num[x][1] + num[x][2], x)));
    S1.erase(P(num[x][pos[x]], x)), S5.insert(P(num[x][pos[x]], x));
    if (pos[x] > 2) S5.erase(P(num[x][pos[x] - 1], x));
    if (pos[x] + 1 < num[x].size()) S1.insert(P(num[x][pos[x] + 1], x));
    pos[x]++;
}

inline void down(int x) {
    if (pos[x] == 3) S4.insert(P(num[x][0] + num[x][1], x)), S6.erase(S6.find(P((LL)num[x][0] + num[x][1] + num[x][2], x))); 
    else {
        if (pos[x] == 4) S6.insert(P((LL)num[x][0] + num[x][1] + num[x][2], x));
        S5.insert(P(num[x][pos[x] - 2], x));
    }
    if (pos[x] < num[x].size()) S1.erase(S1.find(P(num[x][pos[x]], x)));
    S1.insert(P(num[x][pos[x] - 1], x)), S5.erase(S5.find(P(num[x][pos[x] - 1], x)));
    pos[x]--;
}

int main() {
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 1, t, v; i <= n; i++) 
        scanf("%d%d", &t, &v), num[t].push_back(v);
    for (int i = 1; i <= k; i++) if (num[i].size() >= 2) {
        sort(num[i].begin(), num[i].end(), [](int a, int b) { return a > b; });
        insert(i);
    }
    puts("-1");
    LL res = S2.rbegin() -> first; erase(S2.rbegin() -> second);
    printf("%lld\n", res); bool flag = 1;
    for (int i = 3; i <= n; i++) {
        LL A = -1e18, B = A, C = A, D = A;
        if (!flag) {
            if (!S2.size()) { puts("-1"); continue; }
            res += S2.rbegin() -> first, erase(S2.rbegin() -> second), flag = 1;
            printf("%lld\n", res);
            continue;
        }
        if (S2.size() && S5.size()) A = S2.rbegin() -> first - S5.begin() -> first;
        if (S1.size()) B = S1.rbegin() -> first;
        if (S3.size() && S4.size()) C = S3.rbegin() -> first - S4.begin() -> first;
        if (S2.size() >= 2 && S6.size()) D = S2.rbegin() -> first + (++S2.rbegin()) -> first - S6.begin() -> first;
        if (max(max(A, B), max(C, D)) < -1e17) {
            puts("-1"), flag = 0; continue;
        }
        if (A >= B && A >= C && A >= D) {
            int from = S5.begin() -> second, to = S2.rbegin() -> second;
//            cerr << "A: " << from << ' ' << to << endl;
            down(from), erase(to), res += A;
        } else if (B >= A && B >= C && B >= D) {
            int from = S1.rbegin() -> second;
//            cerr << "B: " << from << endl;
            up(from), res += B;
        } else if (C >= A && C >= B && C >= D) {
            int from = S4.begin() -> second, to = S3.rbegin() -> second;
//            cerr << "C: " << from << ' ' << to << endl;
            insert(from), erase(to), up(to), res += C;
        } else {
            int from = S6.begin() -> second, to1 = S2.rbegin() -> second, to2 = (++S2.rbegin()) -> second;
//            cerr << "fuck: " << from << ' ' << to1 << ' ' << to2 << endl;
            down(from), insert(from), erase(to1), erase(to2), res += D;
        }
//        cerr << S4.begin() -> second << ' ' << S3.rbegin() -> second << endl;
     //   cerr << i << endl;
        printf("%lld\n", res);
    }
}
