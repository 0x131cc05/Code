#include <bits/stdc++.h>
using namespace std;

mt19937 rnd((long long)new char + time(0));

const int N = 16;

typedef pair<int, int> P;

vector<P> ed;

int main() {
    vector<int> tmp = {1};
    int tot = 1;
    while (tot <= 14) {
        int pos = rnd() % tmp.size();
        int a = tmp[pos];
        tmp.erase(tmp.begin() + pos);
        tmp.push_back(tot + 1), tmp.push_back(tot + 2);
        ed.push_back(P(a, rnd() % 100000)), ed.push_back(P(a, rnd() % 100000));
        tot += 2;
    }
    cout << tot << endl;
    for (auto t : ed) cout << t.first << ' ' << t.second << endl;
}