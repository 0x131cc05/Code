#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 5006
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
typedef long long ll;
int n , q;
int A[MAXN] , S[MAXN];

pair<ll,int> dp[MAXN] , mx[MAXN];
ll w;
pair<ll,int> que( int l , int r ) {
	dp[l - 1] = mp( 0 , 0 ) , mx[l - 1] = mp( -S[l - 1] , 0 );
	rep( i , l , r ) {
		dp[i] = max( mp( mx[i - 1].fi + S[i] + w , mx[i - 1].se - 1 ) , dp[i - 1] );
		mx[i] = max( mx[i - 1] , mp( dp[i].fi - S[i] , dp[i].se ) );
	}
	return dp[r];
}

void solve() {
	cin >> n >> q;
	rep( i , 1 , n ) scanf("%d",A + i) , S[i] = S[i - 1] + A[i];
//	int las = 0 , del , ld = 0x3f3f3f3f;
//	rep( k , 1 , n ) {
//		int cur = que( 1 , n , k );
//		printf("%d\n",del = cur - las);
//		assert( del <= ld );
//		ld = del;
//		las = cur;
//	}
	rep( i , 1 , q ) {
		int l , r , k;
		scanf("%d%d%d",&l,&r,&k);
		ll L = -1e13 , R = 1e13 , re = -1;
		while( L <= R ) {
			w = ( L + R ) / 2;
			pair<ll,int> as = que( l , r );
			if( -as.se <= k ) re = w , L = w + 1;
			else R = w - 1;
		}
		w = re;
		pair<ll,int> as = que( l , r );
		printf("%lld\n",as.fi - k * re);
	}
}

signed main() {
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
	solve();
}




