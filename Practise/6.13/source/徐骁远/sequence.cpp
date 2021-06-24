#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define dbg(x) cerr << #x << " = " << x << endl
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define MP make_pair
#define pb push_back
typedef long long LL;
typedef unsigned long long ull;
const int N = 50000 + 10;
const int INF = 0x3f3f3f3f3f3f3fll;
template <typename Tp> void read(Tp &x){
	x = 0; int op = 1; char ch = getchar();
	while(!isdigit(ch)){ if(ch == '-') op = -1; ch = getchar(); }
	while(isdigit(ch)){ x = x*10+ch-'0'; ch = getchar(); } x *= op;
}
template <typename Tp> void CMax(Tp &x, Tp y){ if(x < y) x = y; }
template <typename Tp> void CMin(Tp &x, Tp y){ if(y < x) x = y; }

int n, Q, a[N];
int sum[N];
int w(int l, int r){ return sum[r] - sum[l - 1]; }
struct Data{
	int v, p;
	Data(){ v = p = 0; }
	Data(int _v, int _p) : v(_v), p(_p) {}
	bool operator < (const Data &b) const{
		if(v == b.v) return p > b.p;
		return v < b.v;
	}
	Data operator + (const Data &b) {
		return Data(v + b.v, p + b.p);
	}
} f[N];
int delta;
void DP(int l, int r){
	f[l - 1] = Data(0, 0);
	int p = l - 1;
	rep(i, l, r) {
		f[i] = f[i - 1];
		CMax(f[i], f[p] + Data(w(p + 1, i) - delta, 1));
		if(f[p] + Data(-sum[p], 0) < f[i] + Data(-sum[i], 0)) p = i;
	}
}
int solve(int L, int R, int k){
	int l = -500000000, r = 500000000, mid;
	while(l < r){
		mid = (l + r) >> 1; delta = mid;
		DP(L, R);
		if(f[R].p > k) l = mid + 1;
		else r = mid;
	}
	delta = r; DP(L, R);
	return f[R].v + delta * k;
}
signed main()
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	read(n); read(Q);
	rep(i, 1, n) read(a[i]), sum[i] = sum[i - 1] + a[i];
	int l, r, k;
	while(Q -- ){
		read(l); read(r); read(k);
		printf("%lld\n", solve(l, r, k));
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
