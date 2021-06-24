#include <bits/stdc++.h>
#define rep(i, n) for(int i = 0; i < (int)(n); i ++)
#define rep1(i, n) for(int i = 1; i <= (int)(n); i ++)
#define MP make_pair

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const LL INF = 0x3f3f3f3f3f3f3f3f;
typedef pair<__int128, int> info_t;

int n, q, a[50005], ql[50005], qr[50005], qk[50005];

vector<int> ver;
vector<LL> tre[131072][2][2];
vector<LL> conv(const vector<LL>& U, const vector<LL>& V)
{
	vector<LL> ret;
	ret.resize((int)U.size() + (int)V.size() - 1);
	int pi = 0, pj = 0;
	ret[0] = U[0] + V[0];
	while(pi + pj + 1 < (int)ret.size()) {
		LL s0 = pi + 1 == (int)U.size() ? -INF : U[pi + 1] + V[pj], s1 = pj + 1 == (int)V.size() ? -INF : U[pi] + V[pj + 1];
		if(s0 > s1) ret[(++ pi) + pj] = s0;
		else ret[pi + (++ pj)] = s1;
	}
	rep(i, ret.size()) ret[i] = max(ret[i], -INF);
	return ret;
}
vector<LL> cmax(const vector<LL>& U, const vector<LL>& V)
{
	vector<LL> ret;
	ret.resize(max(U.size(), V.size()));
	rep(i, ret.size()) ret[i] = max(i >= (int)U.size() ? -INF : U[i], i >= (int)V.size() ? -INF : V[i]);
	return ret;
}

void init(int id)
{
	int v = id | 65536;
	tre[v][0][0] = {0, a[id]};
	tre[v][0][1] = {-INF, a[id]};
	tre[v][1][0] = {a[id]};
	tre[v][1][1] = {a[id]};
}
void pushup(int v)
{
	rep(i, 2) rep(j, 2)
	tre[v][i][j] = cmax(conv(tre[v << 1][i][0], tre[v << 1 | 1][0][j]), conv(tre[v << 1][i][1], tre[v << 1 | 1][1][j]));
}
void gen_tre()
{
	rep(i, n) init(i);
	int l = 65536, r = 65536 + n;
	while(l < r) {
		for(int i = l; i < r; i ++) ver.push_back(i);
		l >>= 1; r >>= 1;
	}
	rep(i, ver.size()) if(ver[i] < 65536) pushup(ver[i]);
}

LL sl[50005], sr[50005], sv[50005];
info_t ck[50005];

pair<LL, int> qs[50005];
pair<LL, int> seq[15000005];
int pos[131072][2][2], cnt;

info_t ca[2][2], cb[2][2], t0[2][2], t1[2][2];
info_t operator+(const info_t& A, const info_t& B)
{
	return MP(A.first + B.first, A.second + B.second);
}
void merge(info_t arr[][2])
{
	rep(i, 2) rep(j, 2)
	arr[i][j] = max(t0[i][0] + t1[0][j], t0[i][1] + t1[1][j]);
}

void calc()
{
	rep(i, q) qs[i] = MP(sv[i], i);
	sort(qs, qs + q); reverse(qs, qs + q);
	
	int cp = 0;
	rep(i, ver.size()) {
		int v = ver[i];
		rep(j, 2) rep(k, 2) pos[v][j][k] = 0;
	}
	rep(i, q) {
		int cur = qs[i].second;
		while(cp < cnt && seq[cp].first >= sv[cur]) {
			pos[seq[cp].second >> 2][seq[cp].second >> 1 & 1][seq[cp].second & 1] ++; cp ++;
		}
		
		int cl = 65536 | ql[cur], cr = 65536 | qr[cur];
		rep(j, 2) rep(k, 2) ca[j][k] = cb[j][k] = j == 0 && k == 0 ? MP(__int128(0), 0) : MP(-__int128(INF) * INF, 0);
		while(cl < cr) {
			if(cl & 1) {
				rep(j, 2) rep(k, 2) {
					t0[j][k] = ca[j][k]; t1[j][k] = MP(tre[cl][j][k][pos[cl][j][k]] - __int128(sv[cur]) * pos[cl][j][k], pos[cl][j][k]);
				}
				merge(ca);
			}
			if(!(cr & 1)) {
				rep(j, 2) rep(k, 2) {
					t0[j][k] = MP(tre[cr][j][k][pos[cr][j][k]] - __int128(sv[cur]) * pos[cr][j][k], pos[cr][j][k]); t1[j][k] = cb[j][k];
				}
				merge(cb);
			}
			cl = (cl + 1) >> 1; cr = (cr - 1) >> 1;
		}
		if(cl == cr) {
			rep(j, 2) rep(k, 2) {
				t0[j][k] = ca[j][k]; t1[j][k] = MP(tre[cl][j][k][pos[cl][j][k]] - __int128(sv[cur]) * pos[cl][j][k], pos[cl][j][k]);
			}
			merge(ca);
		}
		ck[cur] = max(ca[0][0] + cb[0][0], ca[0][1] + cb[1][0]);
	}
}

LL ans[50005];

int main()
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	
	scanf("%d%d", &n, &q);
	rep(i, n) scanf("%d", &a[i]);
	rep(i, q) {
		scanf("%d%d%d", &ql[i], &qr[i], &qk[i]);
		ql[i] --; qr[i] --;
	}
	
	gen_tre();
	rep(i, ver.size()) {
		int v = ver[i];
		rep(j, 2) rep(k, 2) rep(l, (int)tre[v][j][k].size() - 1)
		seq[cnt ++] = MP(tre[v][j][k][l + 1] - tre[v][j][k][l], v << 2 | j << 1 | k);
	}
	sort(seq, seq + cnt);
	reverse(seq, seq + cnt);
	
	rep(i, q) {
		sl[i] = -INF; sr[i] = INF;
	}
	
	rep(i, 70) {
		rep(j, q) sv[j] = sl[j] + (sr[j] - sl[j] + 1) / 2;
		calc();
		rep(j, q) if(ck[j].second < qk[j]) sr[j] = sv[j] - 1;
		else sl[j] = sv[j];
	}
	
	calc();
	rep(i, q) printf("%lld\n", LL(ck[i].first + __int128(sv[i]) * qk[i]));
	return 0;
}
