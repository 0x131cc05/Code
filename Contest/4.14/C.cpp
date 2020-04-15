#include <bits/stdc++.h>
using namespace std;
const int N = 300010;
struct node {int l, r, mx, tag;} T[N << 2];
inline void pushup(int rt) {T[rt].mx = max(T[rt << 1].mx, T[rt << 1 | 1].mx);}
inline void pushdown(int rt) {
	T[rt << 1].mx += T[rt].tag, T[rt << 1 | 1].mx += T[rt].tag;
	T[rt << 1].tag += T[rt].tag, T[rt << 1 | 1].tag += T[rt].tag, T[rt].tag = 0;
}
int w, h, x[N], y[N], id[N], n;
void build(int rt, int l, int r) {
	T[rt].l = l, T[rt].r = r, T[rt].tag = 0;
	if (l == r) return T[rt].mx = w + y[id[l]], void();
	int mid = (l + r) >> 1; 
	build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r), pushup(rt);
}
void update(int rt, int start, int end, int x) {
	int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
	if (start <= l && r <= end) return T[rt].mx -= x, T[rt].tag -= x, void();
	if (T[rt].tag) pushdown(rt);
	if (start <= mid) update(rt << 1, start, end, x);
	if (end > mid) update(rt << 1 | 1, start, end, x);
	pushup(rt);
}
int query(int rt, int start, int end) {
	int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1; int res = -1e9;
	if (start <= l && r <= end) return T[rt].mx;
	if (T[rt].tag) pushdown(rt);
	if (start <= mid) res = max(res, query(rt << 1, start, end));
	if (end > mid) res = max(res, query(rt << 1 | 1, start, end));
	return res;
}
bool cmp(int a, int b) {return y[a] < y[b];}
int stk1[N], stk2[N], top1, top2;
inline int work() {
	for (int i = 1; i <= n; i++) id[i] = i;
	sort(id + 1, id + n + 1, cmp), y[0] = h, build(1, 1, n), top1 = top2 = 0;
	int mid = w / 2; stk1[0] = stk2[0] = n; int res = 0;
	for (int i = n - 1; i >= 1; i--) {
		int at = id[i];
		res = max(res, 2 * (query(1, i + 1, n) - y[at]));
		//cout << at << ' ' << res << ' ' << y[at] << endl;
		if (x[at] <= mid) {
			update(1, i + 1, stk1[top1], x[at]);
			while (top1 && x[id[stk1[top1]]] <= x[at]) update(1, stk1[top1] + 1, stk1[top1 - 1], x[at] - x[id[stk1[top1]]]), top1--;
			stk1[++top1] = i;
		} else {
			update(1, i + 1, stk2[top2], w - x[at]);
			while (top2 && x[id[stk2[top2]]] >= x[at]) update(1, stk2[top2] + 1, stk2[top2 - 1], x[id[stk2[top2]]] - x[at]), top2--;
			stk2[++top2] = i;
		}
	}
	return res;
}
int main() {
	scanf("%d%d%d", &w, &h, &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);
	x[++ n] = 0; y[n] = 0;
	x[++ n] = w; y[n] = h;
	int res = work(); swap(w, h);
	for (int i = 1; i <= n; i++) swap(x[i], y[i]);
	res = max(res, work()), printf("%d\n", res);
}