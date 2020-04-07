#include <bits/stdc++.h>
using namespace std;
const int N = 50010;
namespace FUCK2 {
	int ch[2][N * 30], sum[N * 30], ncnt, fa[N * 30], val[N * 30];
	inline void connect(int u, int f, int son) {fa[u] = f, ch[son][f] = u;}
    inline bool child(int u) {return u == ch[1][fa[u]];}
    inline void pushup(int u) {sum[u] = sum[ch[0][u]] + sum[ch[1][u]] + 1;}
    inline void rotate(int u) {
        int f = fa[u], ff = fa[f], tmp = child(u), tmp1 = child(f);
        connect(ch[tmp ^ 1][u], f, tmp), connect(f, u, tmp ^ 1), connect(u, ff, tmp1);
        pushup(f), pushup(u);
    }
    inline void splay(int u) {
        for (int f; fa[u]; rotate(u))
            if (fa[f = fa[u]]) rotate(child(u) ^ child(f) ? u : f);
    }
    void Debug(int u) {
		if (!u) return;
		Debug(ch[0][u]), cout << val[u] << ' ', Debug(ch[1][u]);
	}
	inline void insert(int &rt, int v) {
		int nw = rt;
		if (!nw) return rt = ++ncnt, val[rt] = v, sum[rt] = 1, void();
		while (233) {
			int nxt = v > val[nw];
			if (!ch[nxt][nw]) {
//				cout << "before: ", Debug(rt), cout << endl;
//				cout << val[nw] << ' ' << nxt << endl;
				ncnt++, ch[nxt][nw] = ncnt, fa[ncnt] = nw, sum[ncnt] = 1, val[ncnt] = v, splay(ncnt), rt = ncnt;
//				cout << "after: ", Debug(rt), cout << endl;
				return;
			}
			nw = ch[nxt][nw];
		}
	}
	inline int query(int &rt, int x) {
		if (!rt) return 0;
		int nw = rt, res = 0;
		while (233) {
			int nxt = x >= val[nw];
			if (nxt) res += sum[ch[0][nw]] + 1;
			if (!ch[nxt][nw]) return splay(nw), rt = nw, res;
			nw = ch[nxt][nw];
		}
	}
}
int RT1[N * 8], tot;
struct node {int l, r, X, Y;} T[N * 4];
void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r, T[rt].X = ++tot, T[rt].Y = ++tot;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
}
void Update(int rt, int x, int L, int R) {
    int l = T[rt].l, r = T[rt].r;
    FUCK2::insert(RT1[T[rt].X], R), FUCK2::insert(RT1[T[rt].Y], L);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) Update(rt << 1, x, L, R);
    else Update(rt << 1 | 1, x, L, R);
}
int Query(int rt, int start, int end, int x) {
    int l = T[rt].l, r = T[rt].r;
    if (start <= l && r <= end) {
//    	cout << "l, r: " << l << ' ' << r << endl;
//    	cout << "debug L: ", FUCK2::Debug(RT1[T[rt].Y]), cout << endl;
//    	cout << "debug R: ", FUCK2::Debug(RT1[T[rt].X]), cout << endl;
    	return FUCK2::query(RT1[T[rt].Y], x) - FUCK2::query(RT1[T[rt].X], x - 1);	
	}
    int mid = (l + r) >> 1, res = 0;
    if (start <= mid) res += Query(rt << 1, start, end, x);
    if (end > mid) res += Query(rt << 1 | 1, start, end, x);
    return res;
}
struct edge {int to, next;} e[N * 2];
int head[N], ecnt, dfsn, sz[N], son[N], top[N], id[N], fa[N], dep[N], ncnt;
inline void adde(int from, int to) {
    e[++ecnt] = (edge){to, head[from]}, head[from] = ecnt;
    e[++ecnt] = (edge){from, head[to]}, head[to] = ecnt;
}
void dfs1(int u, int f) {
    sz[u] = 1, fa[u] = f, dep[u] = dep[f] + 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs1(e[i].to, u), sz[u] += sz[e[i].to];
            if (sz[e[i].to] > sz[son[u]]) son[u] = e[i].to;
        }
}
void dfs2(int u, int t) {
    id[u] = ++ncnt, top[u] = t;
    if (son[u]) dfs2(son[u], t);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != fa[u] && e[i].to != son[u])
            dfs2(e[i].to, e[i].to);
}
int query(int u, int x, int f) {
	if (dep[u] < dep[f]) cerr << "fuck" << endl;
	if (!u) return 0;
    int res = 0; 
    while (dep[top[u]] >= dep[f]) {
//    	cout << "jump: " << u << ' ' << top[u] << endl;
    	res += Query(1, id[top[u]], id[u], x), u = fa[top[u]];
//    	cout << res << endl;
	}
    if (dep[u] >= dep[f]) res += Query(1, id[f], id[u], x);
    return res;
}
int siz[N], from[N], RT[N], hh[N], cur[N], ans[N]; vector<int> chd[N];
struct fuck1 {int op, a, b, c;} Q[N];
namespace FUCK {
    int sum[N], val[N], fa[N], ch[2][N], ncnt;
    inline void connect(int u, int f, int son) {fa[u] = f, ch[son][f] = u;}
    inline bool child(int u) {return u == ch[1][fa[u]];}
    inline void pushup(int u) {sum[u] = sum[ch[0][u]] + sum[ch[1][u]] + 1;}
    inline void rotate(int u) {
        int f = fa[u], ff = fa[f], tmp = child(u), tmp1 = child(f);
        connect(ch[tmp ^ 1][u], f, tmp), connect(f, u, tmp ^ 1), connect(u, ff, tmp1);
        pushup(f), pushup(u);
    }
    inline void splay(int u) {
        for (int f; fa[u]; rotate(u))
            if (fa[f = fa[u]]) rotate(child(u) ^ child(f) ? u : f);
    }
    inline void insert(int k, int v) {
        if (!ch[0][0]) return ch[0][0] = ++ncnt, val[ncnt] = v, void();
        int nw = ch[0][0];
        while (233) {
            if (sum[ch[0][nw]] >= k - 1) {
                if (!ch[0][nw]) {int t = ++ncnt; ch[0][nw] = t, val[t] = v, sum[t] = 1, fa[t] = nw, splay(t); return;}
                nw = ch[0][nw];
            } else {
                k -= sum[ch[0][nw]] + 1;
                if (!ch[1][nw]) {int t = ++ncnt; ch[1][nw] = t, val[t] = v, sum[t] = 1, fa[t] = nw, splay(t); return;}
                nw = ch[1][nw];
            }
        }
    }
    inline int get(int k) {
        int nw = ch[0][0];
        while (233) {
            if (sum[ch[0][nw]] >= k) nw = ch[0][nw];
            else if (sum[ch[0][nw]] + 1 < k) k -= sum[ch[0][nw]] + 1, nw = ch[1][nw];
            else {splay(nw); return val[nw];}
        }
    }
    void Down(int u, int tmp) {
    	if (!u) return;
    	cur[val[u]] = tmp + sum[ch[0][u]] + 1, Down(ch[0][u], tmp), Down(ch[1][u], cur[val[u]]);
    }
    void Debug(int u) {
    	if (!u) return;
    	Debug(ch[0][u]), cout << val[u] << ' ', Debug(ch[1][u]);
	}
}
bool cmp(int a, int b) {return a > b;}
int main() {
	//freopen("apple1.in","r",stdin), freopen("apple1.out", "w", stdout);
    int n, q, lim; scanf("%d%d", &n, &q);
    for (int i = 1, a, b; i < n; i++) scanf("%d%d", &a, &b), adde(a, b);
    dfs1(1, 0), dfs2(1, 1), build(1, 1, n), lim = 1, FUCK::insert(1, 0), siz[0] = 1, hh[1] = 0, cur[0] = 1, RT[0] = 1;
    for (int i = 1; i <= q; i++) {
        int t; scanf("%d", &t), Q[i].op = t;
        if (t == 1) {
            lim++, scanf("%d%d", &Q[i].a, &Q[i].b), siz[i] = 1;
            from[i] = FUCK::get(Q[i].a), FUCK::insert(Q[i].a + 1, i), RT[i] = Q[i].b;
        } else if (t == 2) {
        	scanf("%d%d%d", &Q[i].a, &Q[i].b, &Q[i].c), Q[i].a = FUCK::get(Q[i].a), Q[i].b = FUCK::get(Q[i].b);
        	//cout << "update: " << Q[i].a << ' ' << Q[i].b << endl;
		}
        else scanf("%d%d", &Q[i].a, &Q[i].b), Q[i].a = FUCK::get(Q[i].a);
        cout << "debug: ", FUCK::Debug(FUCK::ch[0][0]), cout << endl;
    }
    FUCK::Down(FUCK::ch[0][0], 0);
    for (int i = q; i >= 1; i--) if (siz[i]) siz[from[i]] += siz[i], chd[from[i]].push_back(i);
    for (int i = 0; i <= q; i++) if (chd[i].size()) sort(chd[i].begin(), chd[i].end(), cmp);
    for (int i = 1; i <= q; i++) if (cur[i]) hh[cur[i]] = i;
//    for (int i = 1; i <= lim; i++) cout << hh[i] << ' ';
//    cout << endl;
    for (int i = 1; i <= q; i++) {
        if (Q[i].op == 1) ans[i] = ans[from[i]] + query(fa[Q[i].b], cur[from[i]], RT[from[i]]);
        if (Q[i].op == 2) {
        	int pos = lower_bound(chd[Q[i].b].begin(), chd[Q[i].b].end(), i, cmp) - chd[Q[i].b].begin(), r = cur[Q[i].b];
//        	cout << "pos: " << pos << ' ' << Q[i].b << endl;
//        	for (auto v : chd[Q[i].b]) cout << v << ' ';
//        	cout << endl;
            if (pos) {
            	int k = chd[Q[i].b][pos - 1];
				r = cur[k] + siz[k] - 1; 
			}
//            cout << "find:" << Q[i].c << ' ' << cur[Q[i].a] << ' ' << r << endl;
            Update(1, id[Q[i].c], cur[Q[i].a], r);
        } 
        if (Q[i].op == 3) printf("%d\n", query(Q[i].b, cur[Q[i].a], RT[Q[i].a]) + ans[Q[i].a]);
    }
    return 0;
}
