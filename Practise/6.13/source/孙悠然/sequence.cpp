#include <bits/stdc++.h>

using namespace std;

#define FOR(i, x, y) for(int i = (int)(x); i < (int)(y); ++i)
#define REP(i, x, y) for(int i = (int)(x); i <= (int)(y); ++i) 
#define MP make_pair
#define PB push_back
#define fst first
#define snd second
typedef long long ll;

const int maxn = 5e4 + 5;
const int INF = 0x3f3f3f3f;

int n, q;
int a[maxn];
int ql[maxn], qr[maxn], qk[maxn];

namespace WQS{
	int g[maxn];
	ll f[maxn];
	
	inline ll check(int s, int t, ll x){
		f[0] = g[0] = 0;
		ll S = 0;
		pair<ll, int> mx = MP(0, 0);
		REP(i, s, t){
			int it = i - s + 1;
			f[it] = f[it - 1], g[it] = g[it - 1];
			S += a[i];
			if(mx.fst + S + x > f[it] || (mx.fst + S + x == f[it] && mx.snd + 1 < g[it]))
				f[it] = mx.fst + S + x, g[it] = mx.snd + 1;
			if(f[it] - S > mx.fst || f[it] - S == mx.fst && g[it] < mx.snd)
				mx = MP(f[it] - S, g[it]);
		}
		//printf("x = %lld f = %lld g = %d\n", x, f[t - s + 1], g[t - s + 1]);
		return g[t - s + 1];
	}
	
	inline void work(){
		FOR(i, 0, q){
			ll lb = -1e10, rb = 1e10;
			for(; lb + 1 < rb; ){
				ll md = (lb + rb) >> 1;
				if(check(ql[i], qr[i], md) <= qk[i])
					lb = md;
				else
					rb = md;
			}
			
			check(ql[i], qr[i], lb);
			printf("%lld\n", f[qr[i] - ql[i] + 1] - lb * qk[i]);
		}
		return;
	}
}

namespace SEG{
	class SegmentTree{
	public:
		static const int siz = 8192;
		vector<int> dat[siz << 1][2][2];
		
		inline vector<int> minkowski(vector<int> &L, vector<int> &R){
			vector<int> ret; ret.PB(L[0] + R[0]);
			for(int i = 1, j = 1; i < L.size() || j < R.size(); ){
				int lst = ret[ret.size() - 1];
				if(i < L.size() && j < R.size()){
					if(L[i] - L[i - 1] > R[j] - R[j - 1])
						ret.PB(lst + L[i] - L[i - 1]), ++i;
					else
						ret.PB(lst + R[j] - R[j - 1]), ++j;
				}
				else if(i < L.size())
					ret.PB(lst + L[i] - L[i - 1]), ++i;
				else
					ret.PB(lst + R[j] - R[j - 1]), ++j;
			}
			return ret;
		}
		
		inline void build(int x, int l, int r){
			if(l == r){
				FOR(s, 0, 2) FOR(t, 0, 2){
					dat[x][s][t].resize(2);
					FOR(i, 0, 2)
						dat[x][s][t][i] = -INF;
				}
				dat[x][0][0][0] = 0, dat[x][1][1][1] = a[l];
				return;
			}
			
			int md = l + r >> 1;
			build(x << 1, l, md);
			build(x << 1 | 1, md + 1, r);
			
			FOR(s, 0, 2) FOR(t, 0, 2){
				dat[x][s][t].resize(r - l + 2);
				FOR(i, 0, r - l + 2)
					dat[x][s][t][i] = -INF;
				if(!s && !t)
					dat[x][s][t][0] = 0;
			}
			FOR(sl, 0, 2) FOR(tl, 0, 2) FOR(sr, 0, 2) FOR(tr, 0, 2){
				vector<int> vec = minkowski(dat[x << 1][sl][sr], dat[x << 1 | 1][tl][tr]);
				FOR(i, 0, vec.size())
					dat[x][sl][tr][i] = max(dat[x][sl][tr][i], vec[i]);
				if(sr && tl){
					FOR(i, 1, vec.size())
						dat[x][sl][tr][i - 1] = max(dat[x][sl][tr][i - 1], vec[i]);
				}
			}
			return;
		}
		
		inline int query(int s, int t, int k, int x, int l, int r){
			if(l >= s && r <= t){
				int ret = -0x3f3f3f3f;
				FOR(s, 0, 2) FOR(t, 0, 2)
					ret = max(ret, dat[x][s][t][k]);
				return ret;
			}
			int md = l + r >> 1;
			if(t <= md)
				return query(s, t, k, x << 1, l, md);
			return query(s, t, k, x << 1 | 1, md + 1, r);
		}
	} seg;
	
	inline void work(){
		seg.build(1, 0, n - 1);
		FOR(i, 0, q)
			printf("%d\n", seg.query(ql[i], qr[i], qk[i], 1, 0, n - 1));
		return;
	}
}

namespace PSUM{
	int sum[maxn];
	inline void work(){
		FOR(i, 0, n)
			sum[i] = (i ? sum[i - 1] : 0) + a[i];
		FOR(i, 0, q)
			printf("%d\n", sum[qr[i]] - (ql[i] ? sum[ql[i] - 1] : 0));
		return;
	}
}

int main(){
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);

	scanf("%d%d", &n, &q);
	FOR(i, 0, n)
		scanf("%d", a + i);
	FOR(i, 0, q)
		scanf("%d%d%d", ql + i, qr + i, qk + i), --ql[i], --qr[i];
		
	if(n <= 50 && q <= 50 || q == 1)
		WQS::work();
	else if(n == 8192)
		SEG::work();
	else
		PSUM::work();
	return 0;
}
