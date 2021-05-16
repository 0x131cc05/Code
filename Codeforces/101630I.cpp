#include <bits/stdc++.h>
using namespace std;

vector<pair<vector<int>, int>> v;

int num[10010], num1[10010], A, B;

map<pair<int, int>, bool> mp;

bool check(int a, int b) { // e_a < o_b
    if (b > B) return true;
    pair<int, int> nw(a, b);
    if (mp.count(nw)) return mp[nw];
    printf("? %d %d\n", a, b), fflush(stdout);
    char s[5]; scanf("%s", s);
    return mp[nw] = s[0] == '<';
}

int main() {
    int n; scanf("%d", &n), A = n / 2, B = n - A; 
    vector<int> tmp;
    for (int i = 1; i <= B; i++) tmp.push_back(i);
    v.push_back(make_pair(tmp, tmp.size()));
    if (n % 2 == 0) v.push_back(make_pair(vector<int>{ B + 1 }, B + 1));
    for (int i = 1; i <= A; i++) {
        int l = 0, r = (int)v.size() - 1, pos = v.size();
        while (l <= r) {
            int mid = (l + r) >> 1, t = v[mid].first[0];
            if (check(i, t)) pos = mid, r = mid - 1;
            else l = mid + 1;
        }
        auto process = [&](int t) {
            if (t < 0) return false;
            vector<int> L, R;
            for (auto a : v[t].first) 
                if (check(i, a)) R.push_back(a); 
                else L.push_back(a);
            if (!R.size()) return false;
            num[i] = t ? v[t - 1].second : 0;
            if (L.size()) v[t] = make_pair(L, num[i] + L.size()), v.insert(v.begin() + t + 1, make_pair(R, num[i] + L.size() + R.size()));
            num[i] += L.size();
            return true;
        };
        if (!process(pos - 1)) process(pos);
    }
    for (int i = 1; i <= A; i++) num[i] *= 2;
    for (int i = 0; i < v.size(); i++) num1[v[i].first[0]] = v[i].second * 2 - 1;
    printf("! ");
    for (int i = 1; i <= A; i++) printf("%d ", num[i]);
    for (int i = 1; i <= B; i++) printf("%d ", num1[i]);
}