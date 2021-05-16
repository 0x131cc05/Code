#include "graph.h"
using namespace std;

typedef pair<int, int> P;

const int N = 100010;

int pos[N]; // position of i

pair<P, vector<int>> Solve(int n, int m, int T, vector<int> U, vector<int> V, vector<int> p, int subtask) {
    for (int i = 0; i < n; i++) pos[p[i]] = i;
    vector<int> op; vector<P> fuck;
    auto change = [&](int a, int b) {
        pos[p[a]] = b, pos[p[b]] = a, swap(p[a], p[b]);
    };
    for (int i = 0; i < n; i++) if (p[i] != i) 
        fuck.push_back(P(p[i], i)), change(i, pos[i]);
    for (int i = (int)fuck.size() - 1; i >= 0; i--) change(pos[fuck[i].first], pos[fuck[i].second]);
    Answer((int)fuck.size() - 1);
    for (int i = 0; i + 1 < fuck.size(); i++) {
        int u = pos[fuck[i].first], v = pos[fuck[i].second];
        int t = Swap(u, v);
        change(u, v), change(U[t], V[t]), op.push_back(t);
    }
    reverse(op.begin(), op.end());
    return make_pair(P(pos[fuck.back().first], pos[fuck.back().second]), op);
}