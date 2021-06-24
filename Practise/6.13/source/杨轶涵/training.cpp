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
int n , m;
int A[MAXN];

vector<int> G[MAXN];

struct tcurts {
	int u , v , w;
} ed[MAXN];

int dep[MAXN] , fa[MAXN];
void afs( int u , int f ) {
	fa[u] = f;
	for( int v : G[u] ) if( v != f ) {
			dep[v] = dep[u] + 1;
			afs( v , u );
		}
}
int lca( int u , int v ) {
	while( u != v ) {
		if( dep[u] < dep[v] ) v = fa[v];
		else u = fa[u];
	}
	return u;
}

vi E[MAXN];
int dp[MAXN][1 << 10 | 6] , wf[MAXN];
void dfs( int u , int f ) {
	int sz = G[u].size();
	int sw = 0;
	rep( i , 0 , sz - 1 ) {
		int v = G[u][i];
		if( v == f ) continue;
		wf[v] = i;
		dfs( v , u );
		sw += dp[v][0];
	}
	rep( s , 0 , ( 1 << sz ) - 1 ) {
		rep( j , 0 , sz - 1 ) if( ~s & ( 1 << j ) )
			dp[u][s] += dp[G[u][j]][0];
	}
	for( int x : E[u] ) {
		int a = ed[x].u , b = ed[x].v , w = ed[x].w;
		int re = ( a != u ? dp[a][0] : 0 ) + ( b != u ? dp[b][0] : 0 );
		int pwa = -1 , pwb = -1;
		while( a != b ) {
			if( dep[a] > dep[b] )
				pwa = wf[a] , a = fa[a] , re += dp[a][1 << pwa];
			else
				pwb = wf[b] , b = fa[b] , re += dp[b][1 << pwb];
		}
		int ps = 0;
		if( ~pwa ) re -= dp[a][1 << pwa] , ps |= ( 1 << pwa );
		if( ~pwb ) re -= dp[a][1 << pwb] , ps |= ( 1 << pwb );
		rep( s , 0 , ( 1 << sz ) - 1 )
			if( ( s & ps ) == ps ) dp[u][s ^ ps] = max( dp[u][s ^ ps] , dp[u][s] + w + re );
	}
}


void solve() {
	cin >> n >> m;
	rep( i , 1 , m ) {
		int u , v , w;
		scanf("%d%d%d",&u,&v,&w);
		if( !w ) G[u].pb( v ) , G[v].pb( u );
		else {
			ed[i] = (tcurts) { u , v , w };
		}
	}
	afs( 1 , 1 );
	int res = 0 , re = 0;
	rep( i , 1 , m ) if( ed[i].u ) {
		int u = ed[i].u , v = ed[i].v , w = ed[i].w;
		int l = lca( u , v );
		if( ( dep[u] ^ dep[v] ) & 1 ) res += w;
		else E[lca( u , v )].pb( i ) , re += w;
	}
	dfs( 1 , 1 );
	cout << re - dp[1][0] + res << endl;
}

signed main() {
	freopen("training.in","r",stdin);
	freopen("training.out","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
	solve();
}



