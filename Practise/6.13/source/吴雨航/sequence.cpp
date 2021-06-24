#include <bits/stdc++.h>

#define fi first
#define se second
#define DB double
#define U unsigned
#define P std::pair
#define LL long long
#define LD long double
#define pb emplace_back
#define MP std::make_pair
#define SZ(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 5e4 + 5;
int n,q,a[MAXN];

namespace BF{
	inline bool check(){
		return q == 1 || (n <= 50 && q <= 50);
	}

	int b[MAXN];
	
	struct Node{
		LL mn;int cnt;
		Node(LL mn=0,int cnt=0) : mn(mn),cnt(cnt) {}
		inline bool operator < (const Node &t) const {
			if(mn != t.mn) return mn < t.mn;
			return cnt > t.cnt;
		}

		inline Node operator + (const Node &t) const {
			return Node(mn+t.mn,cnt+t.cnt);
		}
	}f[MAXN][2],g[MAXN][2];

	inline Node chk(int n,int k){// 代价是k
		f[0][0] = Node(0,0);f[0][1] = Node(-1e18,0);
		FOR(i,1,n){
			f[i][0] = std::max(f[i-1][0],f[i-1][1]);
			f[i][1] = std::max(f[i-1][0]+Node(b[i]-k,1),f[i-1][1]+Node(b[i],0));
			f[i][1] = std::max(f[i][1],f[i-1][1]+Node(b[i]-k,1));
		}
		return std::max(f[n][0],f[n][1]);
	}

	inline int gao(int n,int k){
		int l = -5e8-1,r = 5e8+1,ans = 0;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(chk(n,mid).cnt <= k) ans = mid,r = mid-1;
			else l = mid+1;
		}
		return chk(n,ans).mn+1ll*k*ans;
	}

	inline void Solve(){
		FOR(i,1,q){
			int l,r,k;scanf("%d%d%d",&l,&r,&k);
			FOR(j,l,r) b[j-l+1] = a[j];
			printf("%d\n",gao(r-l+1,k));
		}
		exit(0);
	}
}

namespace Subtask1{
	inline bool check(){
		bool flag = 1;
		FOR(i,1,n) flag &= (a[i] >= 0);
		return flag;
	}

	int sm[MAXN];

	inline void Solve(){
		FOR(i,1,n) sm[i] = sm[i-1]+a[i];
		FOR(i,1,q){
			int l,r,k;scanf("%d%d%d",&l,&r,&k);
			printf("%d\n",sm[r]-sm[l-1]);
		}
		exit(0);
	}
}

int main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%d%d",&n,&q);
	FOR(i,1,n) scanf("%d",a+i);
	if(Subtask1::check()) Subtask1::Solve();
	if(BF::check()) BF::Solve();
	return 0;
}
