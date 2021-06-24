#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> P;

const int N = 300010;

char s[N];

int main() {
    freopen("number.in", "r", stdin);
    // freopen("number.out", "w", stdout);
    scanf("%s", s + 1); int len = strlen(s + 1);
    set<P> num; int diff = 0;
    for (int i = len; i >= 1; i--) if (s[i] == '1') {
        int j = i;
        while (j != 1 && s[j - 1] == '1') j--;
        num.insert(P(len - i, len - j)), i = j;
    }
    auto plus = [&](int pos) {
        pos += diff;
        while (233) {
            auto t = num.upper_bound(P(pos, 1e9));
            if (t == num.begin()) { num.insert(P(pos, pos)); break; }
            t--;
            if (t -> second < pos) {
                if (t -> second == pos - 1) {
                    P tmp = *t; num.erase(t);
                    tmp.second++, num.insert(tmp);
                } else num.insert(P(pos, pos));
                break;
            }
            int l = t -> first, r = t -> second;
            num.erase(t);
            if (pos != l) num.insert(P(l, pos - 1));
            pos = r + 1;
        }
        auto t = num.upper_bound(P(pos, 1e9)); 
        if (t != num.end()) {
            auto p = t; p--;
            if (p -> second + 1 == t -> first) {
                int l = p -> first, r = t -> second;
                num.erase(p), num.erase(t), num.insert(P(l, r));
            }
        }
    };
    int mx = 0;
    int res = 0;
    while (233) {
        mx = max(mx, num.rbegin() -> second - diff);
        if (*num.rbegin() == P(diff, diff)) break;
        if (num.begin() -> first > diff) {
            res += num.begin() -> first - diff, diff = num.begin() -> first;
        } else {
            vector<int> fk; vector<P> wkr;
            for (auto t : num) 
                fk.push_back(t.second == t.first ? t.second + 1 : t.second + 2), wkr.push_back(t);
            for (auto t : wkr) {
                if (t.first == t.second) continue;
                num.erase(num.find(t)), num.insert(P(t.first, t.first));
                if (t.first + 1 < t.second) num.insert(P(t.first + 2, t.second));
            }
            for (auto t : fk) plus(t - diff);
            plus(0), res++;
        }
    }
    cout << mx << endl;
    printf("%d\n", res);
}