#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef pair<int, int> P;

P pos[N]; int ans[N], id[N], bk[N], n;

void END() { puts("syntax error"), exit(0); }

bool inside(P a, int b) {
    return pos[b].first < a.first && a.first < pos[ans[b]].first && pos[b].second < a.second && a.second < pos[ans[b]].second;
}

void check(int a, int b) {
    assert(a <= n && b <= n);
    P A = P(max(pos[a].first, pos[b].first), max(pos[a].second, pos[b].second));
    P B = P(min(pos[ans[a]].first, pos[ans[b]].first), min(pos[ans[a]].second, pos[ans[b]].second));
    if (A.first > B.first || A.second > B.second) return;
    if (A == pos[a] && B == pos[ans[a]] && inside(A, b) && inside(B, b)) return;
    if (A == pos[b] && B == pos[ans[b]] && inside(A, a) && inside(B, a)) return;
    END();
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n * 2; i++) 
        scanf("%d%d", &pos[i].first, &pos[i].second), id[i] = i;
    sort(id + 1, id + n * 2 + 1, [&](int a, int b) {
        if (pos[a].second != pos[b].second) return pos[a].second > pos[b].second;
        if (pos[a].first != pos[b].first) return pos[a].first > pos[b].first;
        return a > b;
    });
    set<P> s;
    for (int i = 1; i <= n * 2; i++) {
        int cur = id[i];
        if (cur > n) s.insert(P(pos[cur].first, cur));
        else {
            auto tmp = s.lower_bound(P(pos[cur].first, cur));
            if (tmp == s.end()) END();
            ans[cur] = tmp -> second, bk[tmp -> second] = cur, s.erase(tmp);
        }
    }
    if (s.size()) END();
    for (int i = 1; i <= n * 2; i++) {
        int cur = id[i];
        if (cur <= n) s.erase(P(pos[ans[cur]].first, ans[cur]));
        else {
            P nw(pos[cur].first, cur); auto t = s.upper_bound(nw);
            if (t != s.begin()) {
                auto it = t; it--;
                check(bk[it -> second], bk[cur]);
            } 
            if (t != s.end()) check(bk[t -> second], bk[cur]);
            s.insert(nw);
        }
    }
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i] - n);
}