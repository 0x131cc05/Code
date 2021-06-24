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
int n , m , P , iv2;

vector<pii > sg[MAXN];
int ch[MAXN << 1][2] , fa[MAXN << 1] , L[MAXN << 1] , R[MAXN << 1] , rt;


void pu( int rt ) {
	L[rt] = L[ch[rt][0]] , R[rt] = R[ch[rt][1]];
}

void rotate( int u ) {
	if( u == rt ) return;
	int f = fa[u] , g = fa[f] , w = ch[f][1] == u , k = ch[u][w ^ 1];
	if( g ) ch[g][ch[g][1] == f] = u; else rt = u;
	ch[u][w ^ 1] = f , ch[f][w] = k;
	fa[u] = g , fa[k] = f , fa[f] = u;
	pu( f ) , pu( u );
}

namespace bruteforce {
	
	int que( int rt , int l , int r ) {
		if( l <= L[rt] && r >= R[rt] ) return 1;
		int mid = R[ch[rt][0]] , res = 0;
		if( l <= mid ) res += que( ch[rt][0] , l , r );
		if( r > mid ) res += que( ch[rt][1] , l , r );
		return res;
	}
	
	void main() {
		rep( i , 1 , m ) {
			int op , l , r;
			scanf("%d",&op);
			if( op == 1 ) {
				scanf("%d",&l);
				rotate( l );
			} else {
				scanf("%d%d",&l,&r);
				printf("%d\n",que( rt , l , r ));
			}
		}
	}
}

void build( int rt , int l , int r ) {
	if( l == r ) return;
	int ls = sg[l].back( ).se , m = sg[l].back( ).fi , rs = sg[m + 1].back( ).se;
	sg[l].pop_back( ) , sg[m + 1].pop_back( );
	ch[rt][0] = ls , ch[rt][1] = rs , fa[ls] = fa[rs] = rt;
	build( ls , l , m ) , build( rs , m + 1 , r );
}

struct opt {
	int o , l , r;
} Q[MAXN * 3] , tmp[300006];
int cnt = 0;

int T[MAXN];
void add( int x , int c ) {
	while( x <= n ) T[x] += c , x += ( x & -x );
}
int sum( int x ) {
	int ret = 0;
	while( x > 0 ) ret += T[x] , x -= ( x & -x );
	return ret;
}

int as[MAXN];

void cdq( int l , int r ) {
//	cout << l << ' ' << r << endl;
	if( l == r ) return;
	int m = l + r >> 1;
	cdq( l , m ) , cdq( m + 1 , r );
	int lt = l , cn = l - 1;
	rep( i , l , m ) tmp[i - l + 1] = Q[i];
	rep( i , m + 1 , r ) {
		while( lt <= m && tmp[lt - l + 1].l >= Q[i].l ) {
			Q[++ cn] = tmp[lt - l + 1];
			if( tmp[lt - l + 1].o > 0 ) { ++ lt; continue; }
			add( tmp[lt - l + 1].r , tmp[lt - l + 1].o == -2 ? 1 : -1 );
			++ lt;
		}
		Q[++ cn] = Q[i];
		if( Q[i].o < 0 ) continue;
		as[Q[i].o] += sum( Q[i].r );
	}
	rep( i , lt , m ) Q[++ cn] = tmp[i - l + 1];
	rep( i , l , lt - 1 ) if( tmp[i - l + 1].o < 0 ) add( tmp[i - l + 1].r , -( tmp[i - l + 1].o == -2 ? 1 : -1 ) );
}

void solve() {
	cin >> n >> m;
	rep( i , 1 , 2 * n - 1 ) {
		scanf("%d%d",L + i,R + i);
		sg[L[i]].eb( mp( R[i] , i ) );
	}
	rep( i , 1 , n ) sort( all( sg[i] ) );
	rt = sg[1].back().se;
	sg[1].pop_back();
	build( rt , 1 , n );
	if( 0 && n <= 1000 && m <= 1000 ) { bruteforce::main(); return; }
	rep( i , 1 , n * 2 - 1 ) if( L[i] != R[i] ) Q[++ cnt] = (opt) { -1 , L[i] , R[i] };
	rep( i , 1 , m ) {
		int op , l , r;
		scanf("%d",&op);
		if( op == 1 ) {
			scanf("%d",&l);
			as[i] = -114514;
			if( l == rt ) continue;
			Q[++ cnt] = (opt) { -2 , L[l] , R[l] };
			int w = ch[fa[l]][1] == l;
			rotate( l );
			Q[++ cnt] = (opt) { -1 , L[ch[l][w ^ 1]] , R[ch[l][w ^ 1]] };
		}
		else {
			scanf("%d%d",&l,&r);
			Q[++ cnt] = (opt) { i , l , r };
			as[i] = r - l + 1;
		}
	}
//	cerr << cnt << endl;
	cdq( 1 , cnt );
	rep( i , 1 , m ) if( as[i] != -114514 ) printf("%d\n",as[i]);
}

signed main() {
	freopen("c2.in","r",stdin); freopen("c.out","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
	solve();
}






