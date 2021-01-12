#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef long long LL;
typedef pair<int, int> P;

struct node {
	int l, r, tag; LL sum;
} T[N << 2];

void build(int rt, int l, int r) {
	T[rt].l = l, T[rt].r = r;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
}

void pushup(int rt) {
	T[rt].sum = T[rt << 1].sum + T[rt << 1 | 1].sum;
}

void pushdown(int rt) {
	if (!T[rt].tag) return;
	int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
	T[rt << 1].sum += (LL)(mid - l + 1) * T[rt].tag, T[rt << 1 | 1].sum += (LL)(r - mid) * T[rt].tag;
	T[rt << 1].tag += T[rt].tag, T[rt << 1 | 1].tag += T[rt].tag, T[rt].tag = 0;
}

void update(int rt, int start, int end, int x) {
	int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
	if (start <= l && r <= end) return T[rt].tag += x, T[rt].sum += (LL)x * (r - l + 1), void();
	pushdown(rt);
	if (start <= mid) update(rt << 1, start, end, x);
	if (end > mid) update(rt << 1 | 1, start, end, x);
	pushup(rt);
}

LL query(int rt, int start, int end) {
	int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
	if (start <= l && r <= end) return T[rt].sum;
	pushdown(rt); LL res = 0;
	if (start <= mid) res += query(rt << 1, start, end);
	if (end > mid) res += query(rt << 1 | 1, start, end);
	return res;
}

int link[N] = { -1 }, nxt[N][26], len[N], ncnt, last; 

int insert(char c) {
	int nw = ++ncnt, p = last; len[nw] = len[last] + 1, last = nw;
	while (~p && !nxt[p][c - 'a']) nxt[p][c - 'a'] = nw, p = link[p];
	if (!~p) return nw;
	int q = nxt[p][c - 'a'];
	if (len[q] == len[p] + 1) return link[nw] = q, nw;
	int clone = ++ncnt; memcpy(nxt[clone], nxt[q], sizeof(nxt[q]));
	len[clone] = len[p] + 1, link[clone] = link[q], link[q] = link[nw] = clone;
	while (~p && nxt[p][c - 'a'] == q) nxt[p][c - 'a'] = clone, p = link[p];
	return nw;
}

int fa[N], ch[N][2], lst[N];

void connect(int u, int f, int son) {
	fa[u] = f, ch[f][son] = u;
}

bool isroot(int u) {
	return (ch[fa[u]][0] != u && ch[fa[u]][1] != u) || !fa[u]; 
}

void down(int u) {
	if (ch[u][0]) lst[ch[u][0]] = lst[u];
	if (ch[u][1]) lst[ch[u][1]] = lst[u];
}

bool child(int u) {
	return u == ch[fa[u]][1];
}

void rotate(int u) {
	int f = fa[u], ff = fa[f], tmp = child(u), tmp1 = child(f);
	if (!isroot(f)) connect(u, ff, tmp1);
	fa[u] = ff, connect(ch[u][tmp ^ 1], f, tmp), connect(f, u, tmp ^ 1);
}

void splay(int u) {
	static int st[N], top; int p = st[top = 1] = u;
	while (!isroot(p)) st[++top] = p = fa[p];
	while (top) down(st[top--]);
	for (int f; !isroot(u); rotate(u))
		if (!isroot(f = fa[u]))
			rotate(child(u) ^ child(f) ? u : f);
}

void access(int u, int pos) {
	int t = u;
	for (int y = 0; u; y = u, u = fa[u]) {
		splay(u), ch[u][1] = y;
		if (lst[u]) update(1, lst[u] - len[u] + 1, lst[u] - len[fa[u]], -1);
	}
	splay(t), lst[t] = pos, update(1, 1, pos, 1);
}

char s[N];

int pos[N]; vector<P> wkr[N]; LL ans[N];

int main() {
	scanf("%s", s + 1); int n = strlen(s + 1);
	for (int i = 1; i <= n; i++) pos[i] = insert(s[i]);
	for (int i = 1; i <= ncnt; i++) fa[i] = link[i];
	int q; scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		int l, r; scanf("%d%d", &l, &r);
		wkr[r].push_back(P(l, i));
	}
	build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		access(pos[i], i);
		for (auto t : wkr[i]) ans[t.second] = query(1, t.first, i);
	}
	for (int i = 1; i <= q; i++) printf("%lld\n", ans[i]);
}


