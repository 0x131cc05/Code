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
#define MAXN 1000006
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
int n , m , k;
int A[MAXN];
int mn[MAXN][19];

int que( int l , int r ) {
	int p = 31 - __builtin_clz( r - l + 1 );
	return max( mn[l][p] , mn[r - ( 1 << p ) + 1][p] );
}

int as = 0;

int dp[MAXN];
int Q[MAXN] , hd , tl;

bool chk( int x ) {
	queue<int> Q;
	rep( i , 1 , n + 1 ) dp[i] = 0;
	per( i , n , 1 ) {
		while( Q.size() && m - que( i + 1 , Q.front() ) + i * k <= 0 ) Q.pop();
		if( Q.size() ) {
			dp[i] = Q.back();
		}
		if( m + i * k - que( i + 1 , n ) > 0 ) dp[i] = n + 1;
		if( dp[i + x - 1] ) Q.push( i + x - 1 );
	}
	rep( i , 1 , n ) {
		if( m - que( 1 , i ) <= 0 ) break;
		if( dp[i] ) return as = i , true;
	}
	return false;
}

void solve() {
	while( cin >> n >> m >> k ) {
		rep( i , 1 , n ) scanf("%d",A + i);
		rep( i , 1 , n ) A[i] += A[i - 1] , mn[i][0] = A[i];
		rep( t , 1 , 18 ) rep( i , 1 , n - ( 1 << t ) + 1 )
			mn[i][t] = max( mn[i][t - 1] , mn[i + ( 1 << t - 1 )][t - 1] );
//		cout << chk( 1 ) << endl;
		int l = 1 , r = n + 1;
		while( l <= r ) {
			int mid = l + r >> 1;
			if( chk( mid ) ) l = mid + 1;
			else r = mid - 1;
		}
		if( r == 0 ) { puts("Poor Hero!"); continue; }
		if( r == n + 1 ) { puts("Poor JRY!"); continue; }
		cout << r << endl;
		chk( r );
		vi res;
		while( as <= n ) res.pb( as ) , as = dp[as];
		cout << res.size() << endl;
		for( int x : res ) printf("%d ",x); puts("");
	}
}

signed main() {
//	freopen("input","r",stdin);
//	freopen("ot","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
	solve();
}

