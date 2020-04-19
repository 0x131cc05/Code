#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 510 
#define pb push_back 
#define sz size
#define fi first
#define se second
#define qm( a ) a = ( a > P ? a - P : a )
#define P 1000000007
int n , q;
int id = 1;
int rt[MAXN];
vector<int> G[MAXN][MAXN];
int val[MAXN][MAXN];
vector<int> e[MAXN];
int par[MAXN][MAXN];

void dfscop( int w , int to , int u ) {
	val[to][u] = val[w][u];
	for( int i = 0 ; i < G[w][u].size() ; ++ i ) {
		int v = G[w][u][i];
		G[to][u].push_back(v);
		dfscop( w , to , v );
	}
}
void predfs( int u , int fa ) {
	for( int i = 0 ; i < e[u].size() ; ++ i ) {
		int v = e[u][i];
		if( v == fa ) continue;
		G[1][u].pb( v );
		predfs( v , u );
	}
}
int aha;
void add( int w , int u , int qwq ) {
	if( u == aha ) qwq = 1;
	if( qwq ) ++ val[w][u];
	for( int i = 0 ; i < G[w][u].size() ; ++ i ) {
		int v = G[w][u][i];
		add( w , v , qwq );
	}
	if( u == aha ) qwq = 0;
}

int nxt[MAXN];

int main() {
	freopen("apple1.in", "r", stdin), freopen("apple1.ans", "w", stdout);
	cin >> n >> q;
	for( int i = 1 , u , v ; i < n ; ++ i ) {
		scanf("%d%d",&u,&v); 
		e[u].pb( v ) , e[v].pb( u );
	}
	rt[1] = 1;
	predfs( 1 , 1 );
	int opt , a , b , u;
	while( q-- ) {
		scanf("%d",&opt);
		if( opt == 1 ) {
			scanf("%d%d",&a,&b);
			rt[++ id] = b;
			for( int i = 1 , cur = 1 ; i <= a ; ++ i , cur = nxt[cur] ) 
				if( i == a ) nxt[id] = nxt[cur] , nxt[cur] = id , dfscop( cur , id , b );
		} else if( opt == 2 ) {
			scanf("%d%d%d",&a,&b,&u);
			aha = u;
			for( int i = 1 , cur = 1 ; i <= id ; ++ i , cur = nxt[cur] ) if( i >= a && i <= b ) 
				add( cur , rt[cur] , 0 );
			
		} else {
			scanf("%d%d",&a,&b);
			for( int i = 1 , cur = 1 ; i <= a ; ++ i , cur = nxt[cur] ) 
				if( i == a ) 
					printf("%d\n",val[cur][b]); 
		}
	}
}
