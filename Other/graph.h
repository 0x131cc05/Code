#ifndef __INTER_GRAPH_H
#define __INTER_GRAPH_H

#include <bits/stdc++.h>

std::pair<std::pair<int, int>, std::vector<int> > Solve(int n, int m, int T, std::vector<int> U, std::vector<int> V, std::vector<int> p, int subtask);

namespace __inter_graph {

using namespace std;

vector<int> p, U, V;
string result_str[3] = {"WA_0\%lavvnw;hafhaefwaaoijvasf", "PC_30\%apjfabfa;fbwbca;hvw", "AC_100\%afjiwbbaclvgawdhwal;d"};

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine rng(seed);

const int maxn = 100010;

set<int> st; // 环的最左点

int check(int x, int l, int r) {
	return x >= l && x <= r;
}

int subtask, T, cT;
int n, m, answered, ans;

struct DSU {
	int fa[maxn];
	int getroot(int x) {
		return (x == fa[x]) ? x : (fa[x] = getroot(fa[x]));
	}
	void init() {
		for (int i = 0; i < n; i++) fa[i] = i;
	}
};

struct Tree {
	DSU d;
	int fa[maxn], per[maxn], fa_e[maxn], dep[maxn], rt;
	vector<int> edge[maxn], eid[maxn];
	void dfs(int u, int f) {
		for (int i = 0; i < edge[u].size(); i++) {
			int v = edge[u][i];
			if (v != f) {
				dep[v] = dep[u] + 1;
				fa[v] = u, fa_e[v] = eid[u][i];
				dfs(v, u);
			}
		}
	}
	void init() {
		for (int i = 0; i < n; i++) fa[i] = -1, fa_e[i] = -1;
		for (int i = 0; i < m; i++) per[i] = i;
		shuffle(per, per + m, rng);
		d.init();
		for (int i = 0; i < m; i++) {
			int u = U[per[i]], v = V[per[i]];
			int ru = d.getroot(u), rv = d.getroot(v);
			if (ru == rv) continue;
			d.fa[ru] = rv;
			edge[u].push_back(v), edge[v].push_back(u);
			eid[u].push_back(per[i]), eid[v].push_back(per[i]);
		}
		uniform_int_distribution<int> dist(0, n - 1);
		rt = dist(rng);
		dfs(rt, -1);
	}
} tr[3];

struct dat {int mn[3];};

dat operator+(const dat &d1, const dat &d2) {
	dat ret;
	for (int i = 0; i < 3; i++) {
		if (d1.mn[i] == -1) ret.mn[i] = d2.mn[i];
		else if (d2.mn[i] == -1) ret.mn[i] = d1.mn[i];
		else ret.mn[i] = (tr[i].dep[d1.mn[i]] < tr[i].dep[d2.mn[i]] ? d1.mn[i] : d2.mn[i]);
	}
	return ret;
}

struct Node {
	int ch[2], fa;
	dat d, w;
} S[maxn]; // 下标从 1 开始

void pushUp(int rt) {
	S[rt].d = S[S[rt].ch[0]].d + S[S[rt].ch[1]].d + S[rt].w;
}

int getson(int x) {
    return S[S[x].fa].ch[1] == x;
}

void rotate(int x) {
    if (!S[x].fa) return;
    int f = S[x].fa, ff = S[S[x].fa].fa, s = getson(x);
    if (ff) S[ff].ch[getson(f)] = x;
    S[x].fa = ff;
    S[f].ch[s] = S[x].ch[s^1];
    S[S[x].ch[s^1]].fa = f;
    S[x].ch[s^1] = f;
    S[f].fa = x;
    pushUp(f); pushUp(x);
}

void splay(int x) {
    for (int f; S[x].fa; rotate(x)) {
        if (S[f = S[x].fa].fa) {
            rotate((getson(f) == getson(x)) ? f : x);
        }
    }
}

void Quit(int s, string m) {
	cout << result_str[s] << " " << m << endl;
	exit(0);
}

int col[maxn];

void solve() {
	// cal ans (下发文件无)
	for (int i = 0; i < 3; i++) tr[i].init();
	for (int k = 0; k < 3; k++) {
		S[0].d.mn[k] = S[0].w.mn[k] = -1;
		for (int i = 0; i < n; i++) S[i+1].d.mn[k] = S[i+1].w.mn[k] = i;
	}
	{
		int cycle_cnt = 0;
		for (int i = 0; i < n; i++) {
			if (col[i]) continue;
			int t = i;
			++ cycle_cnt;
			do {
				col[t] = cycle_cnt;
				t = p[t];
			} while (!col[t]);
			t = i; st.insert(i);
			while (p[t] != i) {
				S[p[t]+1].ch[0] = t+1;
				S[t+1].fa = p[t]+1;
				pushUp(p[t]+1);
				t = p[t];
			}
		}
		ans = std :: max(n - cycle_cnt - 1, 0);
	}
	pair<pair<int, int>, vector<int> > res = Solve(n, m, T, U, V, p, subtask);
	if (!answered) Quit(0, "没有调用过 Answer 函数");
	if (!check(res.first.first, 0, n-1) || !check(res.first.second, 0, n-1)) Quit(1, "操作不合法");
	if ((int)res.second.size() > ans) Quit(1, "返回的操作序列长度大于答案");
	swap(p[res.first.first], p[res.first.second]);
	for (int i = 0; i < res.second.size(); i++) {
		if (!check(res.second[i], 0, m-1)) Quit(1, "返回的序列不合法");
		swap(p[U[res.second[i]]], p[V[res.second[i]]]);
	}
	int ok = 1;
	for (int i = 0; i < n; i++) if (p[i] != i) Quit(1, "最终排列不满足要求");
	Quit(2, "答案正确");
}

int leftmost(int x) {
	splay(x);
	while (S[x].ch[0]) x = S[x].ch[0];
	splay(x);
	return x;
}

int rightmost(int x) {
	splay(x);
	while (S[x].ch[1]) x = S[x].ch[1];
	splay(x);
	return x;
}

// 单独分出 >= u 的部分，返回不含 u 的部分的根。
int split1(int u) {
	splay(u);
	int r = S[u].ch[0];
	S[r].fa = S[u].ch[0] = 0;
	pushUp(u);
	return r;
}

// 单独分出 <= u 的部分，返回不含 u 的部分的根
int split2(int u) {
	splay(u);
	int r = S[u].ch[1];
	S[r].fa = S[u].ch[1] = 0;
	pushUp(u);
	return r;
}

int Merge(int x, int y) {
	int u = rightmost(x);
	S[u].ch[1] = y; S[y].fa = u;
	pushUp(u);
	return u;
}

int cycle_shift(int u) {
	int v = split1(u);
	return Merge(u, v);
}

void _swap(int u, int v) {
	if (u == v) return;
	++ u, ++ v;
	// 维护环
	int ru = leftmost(u), rv = leftmost(v);
	if (ru == rv) {
		st.erase(ru-1);
		cycle_shift(p[v-1]+1);
		int t = split2(u);
		splay(u), splay(t);
		st.insert(leftmost(u)-1), st.insert(leftmost(t)-1);
	} else {
		st.erase(ru-1), st.erase(rv-1);
		int x = cycle_shift(p[u-1]+1), y = cycle_shift(p[v-1]+1);
		int r = leftmost(Merge(x, y));
		st.insert(r-1);
	}
	swap(p[u-1], p[v-1]);
}

void print() {
	for (int i = 0; i < n; i++) printf("%d ", p[i]);
	puts("");
	for (int i = 1; i <= n; i++) printf("%d ", leftmost(i));
	puts("");
	puts("");
}

void Answer(int x) {
	if (answered) Quit(0, "调用了两次 Answer 函数");
	answered = 1;
	if (x != ans) Quit(0, "传入 Answer 函数的答案错误"); //
}

int Swap(int u, int v) {
	if (!answered) Quit(0, "在调用 Answer 之前调用了 Swap");
	++ cT;
	if (cT >= T) Quit(1, "操作次数超限");
	if (!check(u, 0, n-1) || !check(v, 0, n-1)) Quit(1, "操作不合法");
	_swap(u, v);
	if (st.size() == 1) return -1;
	std::uniform_int_distribution<int> dist1(0, 2);
	int k = dist1(rng);
	int x = * st.rbegin(); splay(x+1);
	int y = S[x+1].d.mn[k];
	if (tr[k].fa[y] == -1) {
		x = * st.begin(); splay(x+1);
		y = S[x+1].d.mn[k];
	}
	int r = tr[k].fa_e[y];
	_swap(U[r], V[r]);
	return r;
}

void main() {
	scanf("%d%d%d%d", &n, &m, &T, &subtask);
	p = vector<int>(n, 0), U = V = vector<int>(m, 0);
	for (int i = 0; i < n; i++) scanf("%d", &p[i]);
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &U[i], &V[i]);
	}
	solve();
}

}

void Answer(int x) { __inter_graph::Answer(x); }

int Swap(int x, int y) { return __inter_graph::Swap(x, y); }

int main() {
    __inter_graph::main();
	return 0;
}

#endif // __INTER_GRAPH_H
