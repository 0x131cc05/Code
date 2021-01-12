#include <bits/stdc++.h>
using namespace std;

const int N = 30;

typedef pair<int, int> P;

int target[N];

class NextAndPrev {
public:
    int getMinimum(int nxt, int pre, string s, string t) {
        if (s == t) return 0;
        int n = s.size();
        memset(target, -1, sizeof(target));
        set<int> fuck; 
        for (int i = 0; i < n; i++) {
            int c = t[i] - 'a', cur = s[i] - 'a';
            fuck.insert(c);
            if (target[cur] < 0) target[cur] = c;
            else if (target[cur] != c) return -1;
        }
        if (fuck.size() == 26) return -1;
        set<P> hh;
        for (int i = 0; i < 26; i++) if (target[i] >= 0)
            hh.insert(P(i - 52, target[i]));
        int res = 1e9;
        for (int turn = 0; turn <= 0; turn++) {
            for (auto t : hh) cout << t.first << ' ' << t.second << endl;
            auto calc = [&]() {
                map<int, int> A, B;
                for (auto t : hh) {
                    if (t.second >= t.first) A[t.second] = max(A[t.second], t.second - t.first);
                    if (t.second <= t.first) B[t.second] = max(B[t.second], t.first - t.second); 
                }
                int res1 = 0, res2 = 0;
                for (auto t : A) res1 += t.second * nxt;
                for (auto t : B) res2 += t.second * pre;
                res = min(res, res1 + res2);
            };
            bool flag = true;
            for (auto a : hh)
                for (auto b : hh) if (a.first < b.first)
                    if (b.second < a.second) flag = false;
            if (flag) calc();
            auto t = *hh.begin(); hh.erase(t);
            hh.insert(P(t.first + 26, t.second));
            cout << turn << ' ' << res << endl;
        }
        return res > 1e8 ? -1 : res;
    }
};

int main() {
    NextAndPrev solver;
    cout << solver.getMinimum(
123,
456,
"pqrs",
"abab"
) << endl;
}
