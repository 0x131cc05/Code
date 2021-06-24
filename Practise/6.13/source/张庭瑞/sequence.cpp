#include <bits/stdc++.h>
using namespace std;
//Fast IO start
namespace io {
	const int BUFSIZE = 1 << 20;
	char ibuf[BUFSIZE + 1], *is = ibuf, *it = ibuf;
	char obuf[BUFSIZE + 1], *os = obuf, *ot = obuf + BUFSIZE;
	inline char read_char() {
		if (is == it) {
			it = (is = ibuf) + fread(ibuf, 1, BUFSIZE, stdin);
			if (is == it) *it++ = EOF;
		}
		return *is++;
	}
	template <class T>
	inline void read_int(T &x) {
		T f = 1;
		char c = read_char();
		while (!isdigit(c)) {
			if (c == '-') f = -1;
			c = read_char();
		}
		x = 0;
		while (isdigit(c)) {
			x = x * 10 + c - '0';
			c = read_char();
		}
		x *= f;
	}
	inline void read_str(char *s) {
		char c = read_char();
		while (c <= ' ') {
			c = read_char();
		}
		while (c > ' ') {
			*s++ = c;
			c = read_char();
		}
		*s = 0;
	}
	inline void flush() {
		fwrite(obuf, 1, os - obuf, stdout);
		os = obuf;
	}
	inline void print_char(char c) {
		*os++ = c;
		if (os == ot) {
			flush();
		}
	}
	template <class T>
	inline void print_int(T x, char c = 0) {
		static char q[40];
		if (!x) {
			print_char('0');
		} else {
			if (x < 0) {
				print_char('-');
				x = -x;
			}
			int top = 0;
			while (x) {
				q[top++] = x % 10 + '0';
				x /= 10;
			}
			while (top--) {
				print_char(q[top]);
			}
		}
		if (c) print_char(c);
	}
	inline void print_str(char *s, char c = 0) {
		while (*s) {
			print_char(*s++);
		}
		if (c) print_char(c);
	}
	struct flusher_t {
		inline ~flusher_t() {
			flush();
		}
	} flusher;
}
using io::read_char;
using io::read_int;
using io::read_str;
using io::print_char;
using io::print_int;
using io::print_str;
//Fast IO end
const int N = 50005;
const long long INF = 1ll << 60;
int n, q, a[N];
vector<long long> tr[N * 2][2][2];
void Merge(vector<long long> &v1, const vector<long long> &v2) {
	while (v1.size() < v2.size()) v1.push_back(-INF);
	for (int i = 0; i < (int)v2.size(); i++) v1[i] = max(v1[i], v2[i]);
}
vector<long long> Sum(const vector<long long> &v1, const vector<long long> &v2) {
	vector<long long> delta;
	int i = 1, j = 1;
	while (i < (int)v1.size() && j < (int)v2.size()) {
		if (v1[i] - v1[i - 1] > v2[j] - v2[j - 1]) delta.push_back(v1[i] - v1[i - 1]), i++;
		else delta.push_back(v2[j] - v2[j - 1]), j++;
	}
	while (i < (int)v1.size()) delta.push_back(v1[i] - v1[i - 1]), i++;
	while (j < (int)v2.size()) delta.push_back(v2[j] - v2[j - 1]), j++;
	vector<long long> ret;
	ret.push_back(v1[0] + v2[0]);
	for (long long &x : delta) ret.push_back(ret.back() + x);
	return ret;
}
void Merge(int x, int l, int r) {
	vector<long long> tmp;
	for (int f1 = 0; f1 < 2; f1++) for (int f2 = 0; f2 < 2; f2++) for (int f3 = 0; f3 < 2; f3++) {
		Merge(tr[x][f1][f3], tmp = Sum(tr[l][f1][f2], tr[r][f2][f3]));
		if (f2) {
			for (int i = 1; i < (int)tmp.size(); i++) {
				if (i + 1 < (int)tmp.size()) tmp[i] = tmp[i + 1];
				else tmp.pop_back();
			}
			Merge(tr[x][f1][f3], tmp);
		}
	}
	Merge(tr[x][1][0], tr[x][1][1]);
	Merge(tr[x][0][1], tr[x][1][1]);
	Merge(tr[x][0][0], tr[x][0][1]);
	Merge(tr[x][0][0], tr[x][1][0]);
}
int pos[N * 2][2][2];
pair<long long, int> pr[N * 2][2][2];
pair<long long, int> Merge(const pair<long long, int> &x, const pair<long long, int> &y) {
  if (x.first == y.first) return x.second < y.second ? x : y;
  else return x.first > y.first ? x : y;
}
pair<long long, int> operator + (const pair<long long, int> &p1, const pair<long long, int> &p2) {
	return make_pair(p1.first + p2.first, p1.second + p2.second);
}
void Upd(int x, long long mid) {
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) {
		int &k = pos[x][i][j];
		while (k < (int)tr[x][i][j].size() - 1 && tr[x][i][j][k + 1] - tr[x][i][j][k] > mid) k++;
		pr[x][i][j] = make_pair(tr[x][i][j][k] - k * mid, k);
	}
}
vector<int> qvec[N];
pair<long long, int> Query(long long mid, int idx) {
	int flag = 0;
	pair<long long, int> res[2];
	for (int x : qvec[idx]) {
		Upd(x, mid);
		if (!flag) {
			flag = 1;
			for (int i = 0; i < 2; i++)
				res[i] = pr[x][0][i];
		} else {
			pair<long long, int> nr[2];
			for (int i = 0; i < 2; i++) {
				nr[i] = Merge(res[0] + pr[x][0][i], res[1] + pr[x][1][i] + make_pair(mid, -1));
			}
			res[0] = nr[0], res[1] = nr[1];
		}
	}
	return Merge(res[0], res[1]);
}
int L[N], R[N], K[N];
long long Lo[N], Hi[N], Mid[N], Ans[N];
int main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	read_int(n);
	read_int(q);
	for (int i = 0; i < n; i++) {
		read_int(a[i]);
		tr[i + n][0][0] = {0, a[i]};
		tr[i + n][0][1] = {-INF, a[i]};
		tr[i + n][1][0] = {-INF, a[i]};
		tr[i + n][1][1] = {-INF, a[i]};
	}
	for (int i = 0; i < q; i++) {
		read_int(L[i]);
		read_int(R[i]);
		read_int(K[i]);
		L[i]--;
		int l = L[i], r = R[i];
		vector<int> vec, tvec;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) vec.push_back(l), l++;
			if (r & 1) r--, tvec.push_back(r);
		}
		reverse(tvec.begin(), tvec.end());
		vec.insert(vec.end(), tvec.begin(), tvec.end());
		qvec[i] = vec;
		Lo[i] = -5e9;
		Hi[i] = 5e9;
	}
	for (int i = n - 1; i; i--) {
		Merge(i, i << 1, i << 1 | 1);
	}
	while (true) {
		int flag = 1;
		vector<int> id;
		for (int i = 0; i < q; i++) {
			if (Lo[i] < Hi[i]) {
				flag = 0;
				Mid[i] = Lo[i] + (Hi[i] - Lo[i]) / 2;
				id.push_back(i);
			}
		}
		for (int i = 1; i < 2 * n; i++) pos[i][0][0] = pos[i][0][1] = pos[i][1][0] = pos[i][1][1] = 0;
		sort(id.begin(), id.end(), [&](int i, int j) {
			return Mid[i] > Mid[j];
		});
		for (int i : id) {
			auto P = Query(Mid[i], i);
			if (P.second <= K[i]) {
				Hi[i] = Mid[i];
				Ans[i] = P.first + Mid[i] * K[i];
			} else Lo[i] = Mid[i] + 1;
		}
		if (flag) break;
	}
	for (int i = 0; i < q; i++) print_int(Ans[i], '\n');
	return 0;
}
