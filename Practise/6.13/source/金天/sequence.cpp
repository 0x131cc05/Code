#include <bits/stdc++.h>

#define eprintf(args...) fprintf(stderr, args)
#define rep(i, n) for (int i = 0; i < (int)(n); ++ i)

int n, q, a[50005], sum[50005];
int ans[50005];
bool obv = true;

inline void update(int &x, int y) {
	if (y > x) x = y;
}

struct Query {
	int l, r, k, i;

	Query(int _l, int _r, int _k, int _i): l(_l), r(_r), k(_k), i(_i) {}
};

std::vector <Query> qry;

const int inf = 0x3f3f3f3f;

struct Node { std::vector <int> val; };

Node maxconv(Node a, Node b) {
	std::vector <int> va, vb;
	rep(i, a.val.size()) if (i) va.push_back(a.val[i] - a.val[i - 1]);
	rep(i, b.val.size()) if (i) vb.push_back(b.val[i] - b.val[i - 1]);
	std::vector <int> vs(va.size() + vb.size());
	std::merge(va.begin(), va.end(), vb.begin(), vb.end(), vs.begin(), std::greater <int> ());
	Node s;
	s.val.push_back(a.val[0] + b.val[0]);
	rep(i, vs.size()) s.val.push_back(s.val.back() + vs[i]);
	return s;
}

Node max(Node a, Node b) {
	Node s;
	s.val.resize(std::max(a.val.size(), b.val.size()), -inf);
	rep(i, a.val.size()) update(s.val[i], a.val[i]);
	rep(i, b.val.size()) update(s.val[i], b.val[i]);
	return s;
}

Node shift(Node a, int k) {
	Node b = a;
	b.val.erase(b.val.begin(), b.val.begin() + k);
	return b;
}

struct Result { Node f[2][2]; };

Result operator + (const Result &a, const Result &b) {
	Result c;
	rep(s0, 2) rep(e0, 2) rep(s1, 2) rep(e1, 2) {
		Node temp = maxconv(a.f[s0][e0], b.f[s1][e1]);
		c.f[s0][e1] = max(c.f[s0][e1], temp);
		if (e0 && s1 && temp.val.size() >= 1)
			c.f[s0][e1] = max(c.f[s0][e1], shift(temp, 1));
	}
	return c;
}

int calc(const Result &a, int k) {
	int ans = -inf;
	if (k < a.f[0][0].val.size()) update(ans, a.f[0][0].val[k]);
	if (k < a.f[1][0].val.size()) update(ans, a.f[1][0].val[k]);
	if (k < a.f[0][1].val.size()) update(ans, a.f[0][1].val[k]);
	if (k < a.f[1][1].val.size()) update(ans, a.f[1][1].val[k]);
	return ans;
}

struct SegmentTree {
	static const int mxn = 1 << 16;
	Result t[mxn << 1];

	void pushup(int x) {
		t[x] = t[x << 1] + t[x << 1 | 1];
	}

	void build(int n, int a[]) {
		rep(i, mxn) rep(f0, 2) rep(f1, 2) t[i + mxn].f[f0][f1].val.push_back(f0 || f1 ? -inf : 0);
		rep(i, n) t[i + mxn].f[1][1].val.push_back(a[i]);
		for (int i = mxn - 1; i; -- i) pushup(i);
	}

	int query(int l, int r, int k) {
		int ans = 0;
		for (l += mxn, r += mxn; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = calc(t[l ++], k);
			if (r & 1) ans = calc(t[-- r], k);
		}
		return ans;
	}
} seg;

const int mxn = 5e4 + 5;
const int B = 256;

std::vector <int> qid[mxn / B];
int ptr;

Result conq_solve(int l, int r) {
	Result ans;
	if (l + 1 == r) {
		rep(f0, 2) rep(f1, 2) ans.f[f0][f1].val.push_back(f0 || f1 ? -inf : 0);
		ans.f[1][1].val.push_back(a[l]);
	} else {
		int m = (l + r) >> 1;
		ans = conq_solve(l, m) + conq_solve(m, r);
	}
	return ans;
}

int main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	scanf("%d %d", &n, &q);
	rep(i, n) scanf("%d", &a[i]), obv &= a[i] >= 0;
	rep(i, n) sum[i + 1] = sum[i] + a[i];
	seg.build(n, a);
	rep(i, q) {
		int l, r, k;
		scanf("%d %d %d", &l, &r, &k);
		-- l;
		if (r - l <= 50) {
			static int dp[55][55][2];
			memset(dp, -0x3f, sizeof(dp));
			dp[0][0][0] = 0;
			for (int i = l; i < r; ++ i) {
				for (int j = 0; j <= k; ++ j) {
					update(dp[i - l + 1][j][0], dp[i - l][j][0]);
					update(dp[i - l + 1][j + 1][1], dp[i - l][j][0] + a[i]);
					update(dp[i - l + 1][j][0], dp[i - l][j][1]);
					update(dp[i - l + 1][j][1], dp[i - l][j][1] + a[i]);
					update(dp[i - l + 1][j + 1][1], dp[i - l][j][1] + a[i]);
				}
			}
			ans[i] = std::max(dp[r - l][k][0], dp[r - l][k][1]);
			continue;
		}
		if (obv) {
			ans[i] = sum[r] - sum[l];
			continue;
		}
		if (l == 0 && r == n) {
			ans[i] = calc(seg.t[1], k);
			continue;
		}
		if (r - l == ((r - l) & -(r - l)) && r % (r - l) == 0) {
			ans[i] = seg.query(l, r, k);
			continue;
		}
		if (true) {
		// if (r - l <= 2 * B) {
			ans[i] = calc(conq_solve(l, r), k);
			continue;
		}
		qid[l / B].push_back(i);
		qry.emplace_back(l, r - 1, k, i);
	}
	rep(i, (n - 1) / B + 1) {
		if (!qid[i].empty()) {
			// wdnmd
		}
	}
	rep(i, q) printf("%d\n", ans[i]);
	return 0;
}
