#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> P;
typedef long long LL;

template<class T> void read(T &x) {
    x = 0; char c = getchar(); bool flag = false;
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (flag) x = -x;
}

template<class T, typename... Tail> void read(T &x, Tail&... tail) {
   read(x), read(tail...);
}

const int N = 100010;

vector<int> G[N], p; vector<P> res;

void adde(int from, int to) {
	res.push_back(P(from, to));
}

set<int> A, B;

int ind[N];

void disable(int u) {
	for (auto v : G[u]) 
		if (!--ind[v]) A.insert(v);
}

int main() {
	freopen("graph.in", "r", stdin), freopen("graph.out", "w", stdout);
	int n, m, k; read(n, m, k);
	for (int i = 1, a, b; i <= m; i++) 
		scanf("%d%d", &a, &b), G[a].push_back(b), ind[b]++;
	for (int i = 1; i <= n; i++) if (!ind[i]) A.insert(i);
	while (A.size() || B.size()) {
//		cout << A.size() << ' ' << B.size() << endl;
		if (A.empty()) {
			assert(p.size());
			int u = *B.rbegin();
			adde(p.back(), u), p.push_back(u), B.erase(u), disable(u);
			continue;
		}
		if (!k) {
			int u = *A.begin();
			disable(u), p.push_back(u), A.erase(u);
			continue;
		}
		if (k + 1 >= A.size()) {
			if (!B.size() || (B.size() && *A.rbegin() > *B.rbegin())) {
//				cout << "in" << endl;
				int u = *A.rbegin(); vector<int> tmp;
				for (auto v : A) if (v != u) tmp.push_back(v), B.insert(v), k--;
				A.clear(), disable(u), p.push_back(u);
				for (auto t : tmp) A.erase(t);
				continue;
			}
		}
		vector<int> tmp;
		for (auto v : A) {
			B.insert(v), tmp.push_back(v);
			if (!--k) break;
		}
		for (auto t : tmp) A.erase(t);
	}
	for (auto t : p) printf("%d ", t);
	printf("\n%d\n", res.size());
	for (auto [a, b] : res) printf("%d %d\n", a, b);
}