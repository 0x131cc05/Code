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
vector<int> G[MAXN];
void solve() {
	freopen("out.out","r",stdin);
	cin >> m;
	int sz = 0;
	rep( i , 1 , m ) {
		int u , v , w;
		scanf("%d%d%d",&u,&v,&w);
		G[u].pb( w ) , G[v].pb( w );
		sz = max( {sz , u , v } );
	}
	rep( i , 1 , sz ) {
		int s = G[i].size();
		sort( all( G[i] ) ) , G[i].erase( unique( all( G[i] ) ) , G[i].end() );
		if( s != G[i].size() ) {
			puts("WTF?");
			exit(0);
		}
	}
	puts("yyh AK ioi!");
}

signed main() {
//    int T;cin >> T;while( T-- ) solve();
    solve();
}
