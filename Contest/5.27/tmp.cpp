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
#define MAXN 200006
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

vector<pii> G[MAXN];
int head[MAXN] , to[MAXN << 1] , nex[MAXN << 1] , wto[MAXN << 1] , ecn = -1;
void ade( int u , int v , int w ) {
    cout << "adde: " << u << ' ' << v << ' ' << w << endl;
   	to[++ ecn] = v , nex[ecn] = head[u] , wto[ecn] = w , head[u] = ecn;
	to[++ ecn] = u , nex[ecn] = head[v] , wto[ecn] = w , head[v] = ecn;
}

void rebuild( int u , int fa ) {
	int last = -1;
	for( auto& t : G[u] ) if( t.fi != fa ) {
		int v = t.fi;
		if( last == -1 ) ade( u , v , t.se ) , last = u;
		else {
			++ n , ade( last , n , 0 ) , ade( n , v , t.se );
			last = n;
		}
		rebuild( v , u );
	}
}

int vis[MAXN] , siz[MAXN] , E , rt , mn;
void getsize( int u , int fa ) {
    siz[u] = 1;
    for( int i = head[u] ; ~i ; i = nex[i] ) {
        int v = to[i];
        if( v == fa || vis[i >> 1] ) continue;
        getsize( v , u );
        siz[u] += siz[v];
    }
}
void getedge( int u , int fa ) {
    for( int i = head[u] ; ~i ; i = nex[i] ) {
        int v = to[i];
        if( v == fa || vis[i >> 1] ) continue;
        if( max( siz[v] , siz[rt] - siz[v] ) < mn ) mn = max( siz[v] , siz[rt] - siz[v] ) , E = ( i >> 1 );
        getedge( v , u );
    }
}
inline int getit( int u ) { rt = u , E = -1 , mn = 0x3f3f3f3f; getsize( u , u ) , getedge( u , u ); return E; }

int cur = 0 , w;
int p[20][MAXN];
void dfs( int u , int f , int d ) {
	p[cur][u] = d * w;
	cout << cur << ' ' << u << ' ' << p[cur][u] << endl;
	for( int i = head[u] ; ~i ; i = nex[i] ) if( !vis[i >> 1] && to[i] != f ) {
		int v = to[i];
		dfs( v , u , d + wto[i] );
	}
}

int mx = 0;
void divide( int e ) {
	++ cur;
	mx = max( mx , cur );
	vis[e] = cur;
	int u = to[e << 1] , v = to[e << 1 | 1];
	cout << "divide: " << u << ' ' << v << endl;
	w = 1 , dfs( u , u , 0 );
	w = -1 , dfs( v , v , wto[e << 1] );
	u = getit( u ) , v = getit( v );
	if( u != -1 ) divide( u );
	if( v != -1 ) divide( v );
	-- cur;
}

void cfs( int u , int f , int val) {
	p[cur][u] += val;
	for( int i = head[u] ; ~i ; i = nex[i] ) if( to[i] != f ) {
		if( vis[i >> 1] < cur ) 
			cfs( to[i] , u , p[cur][u] + wto[i] - p[to[i]][cur] );
		else cfs( to[i] , u , val);
	}
}

void solve() {
	cin >> n;
	int N = n;
	int u , v , w;
	memset( head , -1 , sizeof head );
	rep( i , 2 , n ) {
		scanf("%d%d%d",&u,&v,&w);
		G[u].eb( mp( v , w ) ) , G[v].eb( mp( u , w ) );
	}
	rebuild( 1 , 1 );
	divide( getit( 1 ) );
	rep( i , 1 , mx ) {
		cur = i;
		cfs( i , i , 0);
	}
	cout << mx << endl;
	rep( i , 1 , N ) {
		rep( j , 1 , mx ) printf("%d ",p[i][j]);
		puts(""); 
	}
}

signed main() {
//    int T;cin >> T;while( T-- ) solve();
    solve();
}
