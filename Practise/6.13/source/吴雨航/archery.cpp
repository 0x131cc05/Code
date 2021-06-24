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

const int MAXN = 2e5 + 5;
int n,r,a[MAXN];

namespace BF{
	inline bool check(){
		return n <= 500 && r <= 500;
	}

	int b[MAXN];
	int c[MAXN][2];

	inline int gao(){
		FOR(i,1,2*n) c[(i+1)/2][i%2] = b[i];
		FOR(i,1,r){
			FOR(j,1,n) if(a[c[i][0]] > a[c[i][1]]) std::swap(c[i][0],c[i][1]);
			int t = c[1][1];
			c[1][1] = c[2][0];
			FOR(j,3,n) c[j-1][0] = c[j][0];
			c[n][0] = t;
		}
		FOR(i,1,n) if(c[i][0] == 1 || c[i][1] == 1) return i;
		assert(0);
	}

	inline void Solve(){
		P<int,int> ans=MP(-1e9,-1e9);
		FOR(i,1,2*n){
			if(i%2) continue;
			int t = 0;
			FOR(j,2,i) b[++t] = j;
			b[++t] = 1;
			FOR(j,i+1,2*n) b[++t] = j;
			ans = std::max(ans,MP(-gao(),(i+1)/2));
		}
		printf("%d\n",ans.se);
	}
}

int main(){
	freopen("archery.in","r",stdin);
	freopen("archery.out","w",stdout);
	scanf("%d%d",&n,&r);
	FOR(i,1,2*n) scanf("%d",a+i);
	if(BF::check()) BF::Solve();
	else{
		printf("%d\n",n);
		return 0;
	}
	return 0;
}
